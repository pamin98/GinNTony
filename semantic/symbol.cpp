#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#include "general.hpp"
#include "error.hpp"
#include "symbol.hpp"

Scope *currentScope;
unsigned int quadNext;
unsigned int tempNumber;

static unsigned int hashTableSize;
static SymbolEntry **hashTable;

static struct Type_tag typeConst[] = {
    {TYPE_VOID, NULL, 0, 0},
    {TYPE_INTEGER, NULL, 0, 0},
    {TYPE_BOOLEAN, NULL, 0, 0},
    {TYPE_CHAR, NULL, 0, 0},
    {TYPE_NIL , NULL, 0, 0}
};

const Type typeVoid = &(typeConst[0]);
const Type typeInteger = &(typeConst[1]);
const Type typeBoolean = &(typeConst[2]);
const Type typeChar = &(typeConst[3]);
const Type typeNil = &(typeConst[4]);

typedef unsigned long int HashType;

static HashType PJW_hash(const char *key)
{

    const HashType PJW_OVERFLOW =
        (((HashType)0xf) << (8 * sizeof(HashType) - 4));
    const int PJW_SHIFT = (8 * (sizeof(HashType) - 1));

    HashType h, g;

    for (h = 0; *key != '\0'; key++)
    {
        h = (h << 4) + (*key);
        if ((g = h & PJW_OVERFLOW) != 0)
        {
            h ^= g >> PJW_SHIFT;
            h ^= g;
        }
    }
    return h;
}

void strAppendChar(char *buffer, RepChar c)
{
    switch (c)
    {
    case '\n':
        strcat(buffer, "\\n");
        break;
    case '\t':
        strcat(buffer, "\\t");
        break;
    case '\r':
        strcat(buffer, "\\r");
        break;
    case '\0':
        strcat(buffer, "\\0");
        break;
    case '\\':
        strcat(buffer, "\\\\");
        break;
    case '\'':
        strcat(buffer, "\\'");
        break;
    case '\"':
        strcat(buffer, "\\\"");
        break;
    default:
    {
        char s[] = {'\0', '\0'};

        *s = c;
        strcat(buffer, s);
    }
    }
}

void strAppendString(char *buffer, RepString str)
{
    const char *s;

    for (s = str; *s != '\0'; s++)
        strAppendChar(buffer, *s);
}

void initSymbolTable(unsigned int size)
{
    unsigned int i;

    currentScope = NULL;
    quadNext = 1;
    tempNumber = 1;

    hashTableSize = size;
    hashTable = (SymbolEntry **)allocate(size * sizeof(SymbolEntry *));

    for (i = 0; i < size; i++)
        hashTable[i] = NULL;
}

void destroySymbolTable()
{
    unsigned int i;

    for (i = 0; i < hashTableSize; i++)
        if (hashTable[i] != NULL)
            destroyEntry(hashTable[i]);

    deallocate(hashTable);
}

void openScope()
{
    Scope *newScope = (Scope *)allocate(sizeof(Scope));

    newScope->negOffset = START_NEGATIVE_OFFSET;
    newScope->parent = currentScope;
    newScope->entries = NULL;

    if (currentScope == NULL)
        newScope->nestingLevel = 1;
    else
        newScope->nestingLevel = currentScope->nestingLevel + 1;

    currentScope = newScope;
}

void closeScope()
{
    SymbolEntry *e = currentScope->entries;
    Scope *t = currentScope;

    while (e != NULL)
    {
        SymbolEntry *next = e->nextInScope;

        hashTable[e->hashValue] = e->nextHash;
        destroyEntry(e);
        e = next;
    }

    currentScope = currentScope->parent;
    delete (t);
}

static void insertEntry(SymbolEntry *e)
{
    e->nextHash = hashTable[e->hashValue];
    hashTable[e->hashValue] = e;
    e->nextInScope = currentScope->entries;
    currentScope->entries = e;
}

static SymbolEntry *newEntry(const char *name)
{
    SymbolEntry *e;

    for (e = currentScope->entries; e != NULL; e = e->nextInScope)
        if (strcmp(name, e->id) == 0)
        {
            error("Duplicate identifier: %s", name);
            return NULL;
        }

    e = new SymbolEntry;
    e->id = new char[strlen(name) + 1];

    strcpy((char *)(e->id), name);
    e->hashValue = PJW_hash(name) % hashTableSize;
    e->nestingLevel = currentScope->nestingLevel;
    insertEntry(e);
    return e;
}

SymbolEntry *newVariable(const char *name, Type type)
{
    SymbolEntry *e = newEntry(name);

    if (e != NULL)
    {
        e->entryType = ENTRY_VARIABLE;
        e->eVariable.type = type;
        type->refCount++;
        currentScope->negOffset -= sizeOfType(type);
        e->eVariable.offset = currentScope->negOffset;
    }
    return e;
}

SymbolEntry *newConstant(const char *name, Type type, ...)
{
    SymbolEntry *e;
    va_list ap;

    union
    {
        RepInteger vInteger;
        RepBoolean vBoolean;
        RepChar vChar;
        RepReal vReal;
        RepString vString;
    } value;

    va_start(ap, type);
    switch (type->dtype)
    {
    case TYPE_INTEGER:
        value.vInteger = va_arg(ap, RepInteger);
        break;
    case TYPE_BOOLEAN:
        value.vBoolean = va_arg(ap, int);
        break;
    case TYPE_CHAR:
        value.vChar = va_arg(ap, int);
        break;
    default:
        internal("Invalid type for constant");
    }
    va_end(ap);

    if (name == NULL)
    {
        char buffer[256];

        switch (type->dtype)
        {
        case TYPE_INTEGER:
            sprintf(buffer, "%d", value.vInteger);
            break;
        case TYPE_BOOLEAN:
            if (value.vBoolean)
                sprintf(buffer, "true");
            else
                sprintf(buffer, "false");
            break;
        case TYPE_CHAR:
            strcpy(buffer, "'");
            strAppendChar(buffer, value.vChar);
            strcat(buffer, "'");
            break;
        }
        e = newEntry(buffer);
    }
    else
        e = newEntry(name);

    if (e != NULL)
    {
        e->entryType = ENTRY_CONSTANT;
        e->eConstant.type = type;
        type->refCount++;
        switch (type->dtype)
        {
        case TYPE_INTEGER:
            e->eConstant.value.vInteger = value.vInteger;
            break;
        case TYPE_BOOLEAN:
            e->eConstant.value.vBoolean = value.vBoolean;
            break;
        case TYPE_CHAR:
            e->eConstant.value.vChar = value.vChar;
            break;
        }
    }
    return e;
}

SymbolEntry *newFunction(const char *name)
{
    SymbolEntry *e = lookupEntry(name, LOOKUP_CURRENT_SCOPE, false);

    if (e == NULL)
    {
        e = newEntry(name);
        if (e != NULL)
        {
            e->entryType = ENTRY_FUNCTION;
            e->eFunction.isForward = false;
            e->eFunction.pardef = PARDEF_DEFINE;
            e->eFunction.firstArgument = e->eFunction.lastArgument = NULL;
            e->eFunction.resultType = NULL;
        }
        return e;
    }
    else if (e->entryType == ENTRY_FUNCTION && e->eFunction.isForward)
    {
        e->eFunction.isForward = false;
        e->eFunction.pardef = PARDEF_CHECK;
        e->eFunction.lastArgument = NULL;
        return e;
    }
    else
    {
        error("Duplicate identifier: %s", name);
        return NULL;
    }
}

SymbolEntry *newParameter(const char *name, Type type,
                          PassMode mode, SymbolEntry *f)
{
    SymbolEntry *e;

    if (f->entryType != ENTRY_FUNCTION)
        internal("Cannot add a parameter to a non-function");
    switch (f->eFunction.pardef)
    {
    case PARDEF_DEFINE:
        e = newEntry(name);
        if (e != NULL)
        {
            e->entryType = ENTRY_PARAMETER;
            e->eParameter.type = type;
            type->refCount++;
            e->eParameter.mode = mode;
            e->eParameter.next = NULL;
        }
        if (f->eFunction.lastArgument == NULL)
            f->eFunction.firstArgument = f->eFunction.lastArgument = e;
        else
        {
            f->eFunction.lastArgument->eParameter.next = e;
            f->eFunction.lastArgument = e;
        }
        return e;
    case PARDEF_CHECK:
        e = f->eFunction.lastArgument;
        if (e == NULL)
            e = f->eFunction.firstArgument;
        else
            e = e->eParameter.next;
        if (e == NULL)
            error("More parameters than expected in redeclaration "
                  "of function %s",
                  f->id);
        else if (!equalType(e->eParameter.type, type))
            error("Parameter type mismatch in redeclaration "
                  "of function %s",
                  f->id);
        else if (e->eParameter.mode != mode)
            error("Parameter passing mode mismatch in redeclaration "
                  "of function %s",
                  f->id);
        else if (strcmp(e->id, name) != 0)
            error("Parameter name mismatch in redeclaration "
                  "of function %s",
                  f->id);
        else
            insertEntry(e);
        f->eFunction.lastArgument = e;
        return e;
    case PARDEF_COMPLETE:
        fatal("Cannot add a parameter to an already defined function");
    }
    return NULL;
}

static unsigned int fixOffset(SymbolEntry *args)
{
    if (args == NULL)
        return 0;
    else
    {
        unsigned int rest = fixOffset(args->eParameter.next);

        args->eParameter.offset = START_POSITIVE_OFFSET + rest;
        if (args->eParameter.mode == PASS_BY_REFERENCE)
            return rest + 2;
        else
            return rest + sizeOfType(args->eParameter.type);
    }
}

void declareFunction(SymbolEntry *f)
{
    if (f->entryType != ENTRY_FUNCTION)
        internal("Cannot make a non-function forward");
    f->eFunction.isForward = true;
}

void endFunctionHeader(SymbolEntry *f, Type type)
{
    if (f->entryType != ENTRY_FUNCTION)
        internal("Cannot end parameters in a non-function");
    switch (f->eFunction.pardef)
    {
    case PARDEF_COMPLETE:
        internal("Cannot end parameters in an already defined function");
        break;
    case PARDEF_DEFINE:
        fixOffset(f->eFunction.firstArgument);
        f->eFunction.resultType = type;
        type->refCount++;
        break;
    case PARDEF_CHECK:
        if ((f->eFunction.lastArgument != NULL &&
             f->eFunction.lastArgument->eParameter.next != NULL) ||
            (f->eFunction.lastArgument == NULL &&
             f->eFunction.firstArgument != NULL))
            error("Fewer parameters than expected in redeclaration "
                  "of function %s",
                  f->id);
        if (!equalType(f->eFunction.resultType, type))
            error("Result type mismatch in redeclaration of function %s",
                  f->id);
        break;
    }
    f->eFunction.pardef = PARDEF_COMPLETE;
    currentScope->returnType = type;
}

SymbolEntry *newTemporary(Type type)
{
    char buffer[10];
    SymbolEntry *e;

    sprintf(buffer, "$%d", tempNumber);
    e = newEntry(buffer);

    if (e != NULL)
    {
        e->entryType = ENTRY_TEMPORARY;
        e->eVariable.type = type;
        type->refCount++;
        currentScope->negOffset -= sizeOfType(type);
        e->eTemporary.offset = currentScope->negOffset;
        e->eTemporary.number = tempNumber++;
    }
    return e;
}

void destroyEntry(SymbolEntry *e)
{
    SymbolEntry *args;

    switch (e->entryType)
    {
    case ENTRY_VARIABLE:
        destroyType(e->eVariable.type);
        break;
    case ENTRY_CONSTANT:
        destroyType(e->eConstant.type);
        break;
    case ENTRY_FUNCTION:
        args = e->eFunction.firstArgument;
        while (args != NULL)
        {
            SymbolEntry *p = args;

            destroyType(args->eParameter.type);
            delete ((char *)(args->id));
            args = args->eParameter.next;
            delete (p);
        }
        destroyType(e->eFunction.resultType);
        break;
    case ENTRY_PARAMETER:

        return;
    case ENTRY_TEMPORARY:
        destroyType(e->eTemporary.type);
        break;
    }
    delete ((char *)(e->id));
    delete (e);
}

SymbolEntry *lookupEntry(const char *name, LookupType type, bool err)
{
    unsigned int hashValue = PJW_hash(name) % hashTableSize;
    SymbolEntry *e = hashTable[hashValue];

    switch (type)
    {
    case LOOKUP_CURRENT_SCOPE:
        while (e != NULL && e->nestingLevel == currentScope->nestingLevel)
            if (strcmp(e->id, name) == 0)
                return e;
            else
                e = e->nextHash;
        break;
    case LOOKUP_ALL_SCOPES:
        while (e != NULL)
            if (strcmp(e->id, name) == 0)
                return e;
            else
                e = e->nextHash;
        break;
    }

    if (err)
        error("Unknown identifier: %s", name);
    return NULL;
}

// Type typeArray(RepInteger size, Type refType)
// {
//     Type n = (Type)allocate(sizeof(struct Type_tag));

//     n->dtype = TYPE_ARRAY;
//     n->refType = refType;
//     n->size = size;
//     n->refCount = 1;

//     refType->refCount++;

//     return n;
// }

Type typeIArray(Type refType)
{
    Type n = (Type)allocate(sizeof(struct Type_tag));

    n->dtype = TYPE_IARRAY;
    n->refType = refType;
    n->refCount = 1;

    refType->refCount++;

    return n;
}

Type typeList(Type refType)
{
    Type n = (Type)allocate(sizeof(struct Type_tag));

    n->dtype = TYPE_LIST;
    n->refType = refType;
    n->refCount = 1;

    refType->refCount++;

    return n;
}

void destroyType(Type type)
{
    switch (type->dtype)
    {
    case TYPE_IARRAY:
    case TYPE_LIST:
        if (--(type->refCount) == 0)
        {
            destroyType(type->refType);
            delete (type);
        }
    }
}

unsigned int sizeOfType(Type type)
{
    switch (type->dtype)
    {
    case TYPE_VOID:
        internal("Type void has no size");
        break;
    case TYPE_INTEGER:
    case TYPE_IARRAY:
    case TYPE_LIST:
        return 2;
    case TYPE_BOOLEAN:
    case TYPE_CHAR:
        return 1;
    }
    return 0;
}

bool equalType(Type type1, Type type2)
{
    if (type1->dtype != type2->dtype)
        return false;
    switch (type1->dtype)
    {
    case TYPE_IARRAY:
    case TYPE_LIST:
        return equalType(type1->refType, type2->refType);
    }
    return true;
}

void printType(Type type)
{
    if (type == NULL)
    {
        printf("<undefined>");
        return;
    }

    switch (type->dtype)
    {
    case TYPE_VOID:
        printf("void");
        break;
    case TYPE_INTEGER:
        printf("integer");
        break;
    case TYPE_BOOLEAN:
        printf("boolean");
        break;
    case TYPE_CHAR:
        printf("char");
        break;
    case TYPE_IARRAY:
        printf("array of ");
        printType(type->refType);
        break;
    case TYPE_LIST:
        printf("^");
        printType(type->refType);
        break;
    }
}

void printMode(PassMode mode)
{
    if (mode == PASS_BY_REFERENCE)
        printf("var ");
}

const char *TypeToStr(Type type)
{
    if (type == NULL)
    {
        return "<undefined>";
    }
    char buffer[1024];
    switch (type->dtype)
    {
    case TYPE_VOID:
        return "void";
    case TYPE_INTEGER:
        return "integer";
    case TYPE_BOOLEAN:
        return "boolean";
    case TYPE_CHAR:
        return "char";
    case TYPE_IARRAY:
        sprintf(buffer, "array of %s", TypeToStr(type->refType));
        return strdup(buffer);
    case TYPE_LIST:
        sprintf(buffer, "list of %s", TypeToStr(type->refType));
        return strdup(buffer);
    case TYPE_NIL:
        return "nil";
    }
    return "undefined";
}
