#ifndef __SYMBOL_HPP__
#define __SYMBOL_HPP__

#include <stdbool.h>

#if 0
typedef enum { false=0, true=1 } bool;
#endif

#define START_POSITIVE_OFFSET 8
#define START_NEGATIVE_OFFSET 0

typedef int RepInteger;
typedef unsigned char RepBoolean;
typedef char RepChar;
typedef long double RepReal;
typedef const char *RepString;

typedef struct Type_tag *Type;

enum dataType
{
   TYPE_VOID,
   TYPE_INTEGER,
   TYPE_BOOLEAN,
   TYPE_CHAR,
   TYPE_IARRAY,
   TYPE_LIST,
   TYPE_NIL
};

enum ParDef
{
   PARDEF_COMPLETE,
   PARDEF_DEFINE,
   PARDEF_CHECK
};

struct Type_tag
{
   dataType dtype;
   Type refType;
   RepInteger size;
   unsigned int refCount;
};

typedef enum
{
   ENTRY_VARIABLE,
   ENTRY_CONSTANT,
   ENTRY_FUNCTION,
   ENTRY_PARAMETER,
   ENTRY_TEMPORARY
} EntryType;

typedef enum
{
   PASS_BY_VALUE,
   PASS_BY_REFERENCE
} PassMode;

typedef struct SymbolEntry_tag SymbolEntry;

struct SymbolEntry_tag
{
   const char *id;
   EntryType entryType;
   unsigned int nestingLevel;
   unsigned int hashValue;
   SymbolEntry *nextHash;
   SymbolEntry *nextInScope;

   union
   {
      struct
      {
         Type type;
         int offset;
      } eVariable;

      struct
      {
         Type type;
         union
         {
            RepInteger vInteger;
            RepBoolean vBoolean;
            RepChar vChar;
            RepReal vReal;
            RepString vString;
         } value;
      } eConstant;

      struct
      {
         bool isForward;
         SymbolEntry *firstArgument;
         SymbolEntry *lastArgument;
         Type resultType;
         ParDef pardef;
         int firstQuad;
      } eFunction;

      struct
      {
         Type type;
         int offset;
         PassMode mode;
         SymbolEntry *next;
      } eParameter;

      struct
      {
         Type type;
         int offset;
         int number;
      } eTemporary;

   };
};


typedef struct Scope_tag Scope;


struct Scope_tag
{
   unsigned int nestingLevel;
   unsigned int negOffset;
   Scope *parent;
   SymbolEntry *entries;
   Type returnType;
   //SymbolEntry currentFunction;
};

typedef enum
{
   LOOKUP_CURRENT_SCOPE,
   LOOKUP_ALL_SCOPES
} LookupType;

extern Scope *currentScope;
extern unsigned int quadNext;
extern unsigned int tempNumber;

extern const Type typeVoid;
extern const Type typeInteger;
extern const Type typeBoolean;
extern const Type typeChar;
extern const Type typeNil;

void initSymbolTable(unsigned int size);
void destroySymbolTable(void);

void openScope(void);
void closeScope(void);

SymbolEntry *newVariable(const char *name, Type type);
SymbolEntry *newConstant(const char *name, Type type, ...);
SymbolEntry *newFunction(const char *name);
SymbolEntry *newParameter(const char *name, Type type,
                          PassMode mode, SymbolEntry *f);
SymbolEntry *newTemporary(Type type);

void declareFunction(SymbolEntry *f);
void endFunctionHeader(SymbolEntry *f, Type type);
void destroyEntry(SymbolEntry *e);
SymbolEntry *lookupEntry(const char *name, LookupType type,
                         bool err);

Type typeArray(RepInteger size, Type refType);
Type typeIArray(Type refType);
Type typeList(Type refType);
void destroyType(Type type);
unsigned int sizeOfType(Type type);
bool equalType(Type type1, Type type2);
void printType(Type type);
void printMode(PassMode mode);
const char *TypeToStr(Type type);

#endif
