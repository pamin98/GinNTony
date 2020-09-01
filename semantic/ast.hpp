#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <symbol.cpp>
#include <error.hpp>

/********************************************************************
			HEY! CHECK OUT THE "SEM COMPLETED" SECTION!
 ********************************************************************/

enum relOp
{
	eq,
	lt,
	gt,
	le,
	ge,
	neq
};

enum logOp
{
	AND,
	OR,
	NOT,
	TRUE,
	FALSE
};

enum listOp
{
	nil,
	nilq,
	head,
	tail,
	append
};

typedef enum HeaderType
{
	Func_Decl,
	Func_Def
} HeaderType;

class Stmt : public AST
{
};

class ExitStmt : public Stmt
{
public:
	ExitStmt() {}
	~ExitStmt() {}
};

class ReturnStmt : public Stmt
{
public:
	ReturnStmt(Expr *e) : returnExpr(e) {}
	~ReturnStmt() {}

private:
	Expr *returnExpr;
};

class SkipStmt : public Stmt
{
public:
	SkipStmt() {}
	~SkipStmt() {}
};

class ListOp : public Expr
{
public:
	ListOp(listOp o, Expr *l = NULL, Expr *r = NULL) : left(l), op(o), right(r) {}
	~ListOp()
	{
		delete left;
		delete right;
	}

private:
	Expr *left;
	listOp op;
	Expr *right;
};

class StmtList : public Stmt
{
public:
	StmtList(Stmt *s)
	{
		stmt_list.push_back(s);
	}
	~StmtList()
	{
		for (Stmt *s : stmt_list)
			delete s;
	}
	void append(Stmt *s) { stmt_list.push_back(s); }

private:
	std::vector<Stmt *> stmt_list;
};

class For : public Stmt
{
public:
	For(StmtList *s1, Expr *e, StmtList *s2, StmtList *s3) : initializers(s1), threshold(e), steps(s2), loop_body(s3) {}
	~For()
	{
		delete threshold;
		delete initializers;
		delete steps;
		delete loop_body;
	}

private:
	Expr *threshold;
	Stmt *initializers;
	Stmt *steps;
	StmtList *loop_body;
};

class If : public Stmt
{
public:
	If(Expr *c, StmtList *s, If *next = NULL) : cond(c), stmt_list(s), nextIf(next) {}
	~If()
	{
		delete cond;
		delete stmt_list;
		delete nextIf;
	}
	void append(If *i) { nextIf = i; }

private:
	Expr *cond;
	StmtList *stmt_list;
	If *nextIf;
};

class ArrayIndexing : public Expr
{
public:
	ArrayIndexing(Expr *a, Expr *i) : array(a), index(i) {}
	~ArrayIndexing()
	{
		delete array;
		delete index;
	}

private:
	Expr *array;
	Expr *index;
};

class ArrayInit : public Expr
{
public:
	ArrayInit(std::string *t, Expr *e) : type(t), expr(e){};
	~ArrayInit()
	{
		delete type;
		delete expr;
	}

private:
	std::string *type;
	Expr *expr;
};

/****************************************************************************************************************
 ************************************************ SEM COMPLETED *************************************************
 ***************************************************************************************************************/
class AST
{
public:
	virtual ~AST() {}
	virtual void sem() {}
};

class Expr : public AST
{
public:
	//virtual int eval() const = 0;
	void type_check(Type t)
	{
		sem();
		if (!equalType(t, type))
			error("Invalid type of operand. Expected %s, got %s.", TypeToStr(t), TypeToStr(type));
	}

	Type get_type()
	{
		sem();
		return type;
	}

	virtual void checkLVal() {}

protected:
	Type type;
};

class Var : public Expr
{
public:
	Var(const char *v) : var(v) {}

	virtual void sem() override
	{
		SymbolEntry *e = lookupEntry(var, LOOKUP_ALL_SCOPES, true);
		type = e->u.eVariable.type;
	}

private:
	const char *var;
};

class VarList : public Expr
{
public:
	VarList(const char *v) { var_list.push_back(v); }

	std::vector<const char *> getList()
	{
		return var_list;
	}

	void append(const char *v) { var_list.push_back(v); }

private:
	std::vector<const char *> var_list;
};

class Formal : public AST
{
public:
	Formal(Type t, VarList *v, bool isRef = false) : type(t), var_list(v)
	{
		if (isRef)
			mode = PASS_BY_REFERENCE;
		else
			mode = PASS_BY_VALUE;
	}
	~Formal()
	{
		delete var_list;
	}

	virtual void passParameters(SymbolEntry *f)
	{
		for (const char *v : var_list->getList())
			SymbolEntry *e = newParameter(v, type, mode, f);
	}

private:
	Type type;
	VarList *var_list;
	PassMode mode;
};

class FormalList : public AST
{
public:
	FormalList() {}
	~FormalList() {}

	void append(Formal *f) { formal_list.push_back(f); }

	virtual void passParameters(SymbolEntry *f)
	{
		// TODO thelei symbolEntry input iparxei mperdema meta3i ton dio f edw
		for (Formal *formal : formal_list)
			formal->passParameters(f);
	}

private:
	std::vector<Formal *> formal_list;
};

class Header : public AST
{
public:
	Header(const char *v, FormalList *fl, Type t, HeaderType D) : functionName(v), formal_list(fl), type(t), T(D) {}
	~Header()
	{
		delete functionName;
		delete formal_list;
		delete type;
	}

	virtual void sem() override
	{
		/* newFunction performs check for duplicate declaration in the same scope */
		SymbolEntry *f = newFunction(functionName);
		if (!T) /* Declarations should be forwarded */
			declareFunction(f);
		openScope();
		formal_list->passParameters(f);
		endFunctionHeader(f, type);
		closeScope(); /* check scopes here !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	}

private:
	const char *functionName;
	FormalList *formal_list;
	Type type;
	HeaderType T;
};

class Definition : public AST
{
};

class DefinitionList : public AST
{
public:
	DefinitionList() : definition_list() {}
	~DefinitionList() {}

	void append(Definition *d) { definition_list.push_back(d); }

	virtual void sem() override
	{
		for (Definition *d : definition_list)
			d->sem();
	}

private:
	std::vector<Definition *> definition_list;
};

class FunctionDefinition : public Definition
{
public:
	FunctionDefinition(Header *h, DefinitionList *dl = NULL, StmtList *sl = NULL) : header(h), def_list(dl), stmt_list(sl) {}
	~FunctionDefinition()
	{
		delete header;
		delete def_list;
		delete stmt_list;
	}

	void setDefinitionList(DefinitionList *dl)
	{
		def_list = dl;
	}

	void setStmtList(StmtList *sl)
	{
		stmt_list = sl;
	}

	virtual void sem() override
	{
		openScope();
		header->sem();
		def_list->sem();
		stmt_list->sem();
		closeScope();
	}

private:
	Header *header;
	DefinitionList *def_list;
	StmtList *stmt_list;
};

class FunctionDeclaration : public Definition
{
public:
	FunctionDeclaration(Header *h) : header(h) {}
	~FunctionDeclaration()
	{
		delete header;
	}

	virtual void sem() override
	{
		openScope();
		header->sem();
		closeScope();
	}

private:
	Header *header;
};

class VarDefinition : public Definition
{
public:
	VarDefinition(Type t, VarList *v) : type(t), var_list(v) {}
	~VarDefinition()
	{
		delete var_list;
		delete type;
	}

	virtual void sem() override
	{
		for (const char *variable : var_list->getList())
			SymbolEntry *e = newVariable(variable, type);
	}

private:
	Type type;
	VarList *var_list;
};

class ExprList : public Expr
{
public:
	ExprList() : expr_list() {}
	~ExprList()
	{
		for (Expr *e : expr_list)
			delete e;
	}

	std::vector<Expr *> getList()
	{
		return expr_list;
	}

	void append(Expr *e) { expr_list.push_back(e); }

private:
	std::vector<Expr *> expr_list;
};

class CallObject : public Expr, public Stmt
{
public:
	CallObject(const char *n, ExprList *e) : functionName(n), expr_list(e) {}
	~CallObject()
	{
		delete functionName;
		delete expr_list;
	}

	virtual void sem() override
	{
		int functionArguments = 0;
		bool argMismatch = false;
		// TODO fix lookupEntry needs more arguments
		SymbolEntry *f = lookupEntry(functionName, LOOKUP_ALL_SCOPES, true);
		if (f->u.eFunction.isForward)
			error("Function %s declared but not defined.", functionName);
		type = f->u.eFunction.resultType;
		SymbolEntry *args;
		args = f->u.eFunction.firstArgument;
		for (Expr *e : expr_list->getList())
		{
			Type paramType;
			if (args)
			{
				++functionArguments;
				paramType = args->u.eParameter.type;
			}
			else
			{
				argMismatch = true;
				break;
			}
			e->type_check(paramType);
			args = args->u.eParameter.next;
		}
		if (argMismatch)
			error("Expected %d arguments for function %s, but %lu were given.",
				  functionArguments, functionName, expr_list->getList().size());
		else if (args)
		{
			while (args)
			{
				++functionArguments;
				args = args->u.eParameter.next;
			}
			error("Expected %d arguments for function %s, but %lu were given.",
				  functionArguments, functionName, expr_list->getList().size());
		}
	}

	virtual void checkLVal() override
	{
		error("Lvalue cannot be a function call.");
	}

private:
	const char *functionName;
	ExprList *expr_list;
};

class ConstString : public Expr
{
public:
	ConstString(const char *str) : str(str) {}

	virtual void sem() override
	{
		type = typeIArray(typeChar);
	}

	virtual void checkLVal() override
	{
		error("Lvalue cannot be a string literal.");
	}

private:
	const char *str;
};

class ConstInt : public Expr
{
public:
	ConstInt(int n) : num(n) {}

	virtual void sem() override
	{
		type = typeInteger;
	}

private:
	int num;
};

class AssignStmt : public Stmt
{
public:
	AssignStmt(Expr *l, Expr *r) : left(l), right(r) {}
	~AssignStmt()
	{
		delete left;
		delete right;
	}

	virtual void sem() override
	{
		left->checkLVal();
		Type ltype = left->get_type();
		right->type_check(ltype);
	}

private:
	Expr *left;
	Expr *right;
};

class BinOp : public Expr
{
public:
	BinOp(Expr *l, char o, Expr *r) : left(l), op(o), right(r) {}
	~BinOp()
	{
		delete left;
		delete right;
	}

	virtual void sem() override
	{
		right->type_check(typeInteger);
		if (left)
			left->type_check(typeInteger);
		type = typeInteger;
	}

private:
	Expr *left;
	char op;
	Expr *right;
};

class RelOp : public Expr
{
public:
	RelOp(Expr *l, relOp o, Expr *r) : left(l), op(o), right(r) {}
	~RelOp()
	{
		delete left;
		delete right;
	}

	virtual void sem() override
	{
		Type leftType = left->get_type();
		Type rightType = right->get_type();
		if (!equalType(leftType, rightType))
			error("Operands of comparison have different types: %s and %s.", TypeToStr(leftType), TypeToStr(rightType));
		if (leftType->dtype == TYPE_INTEGER || leftType->dtype == TYPE_BOOLEAN || leftType->dtype == TYPE_CHAR)
		{
			type = typeBoolean;
			return;
		}
		else
			error("Comparisons supported only for integers, booleans and characters.");
	}

private:
	Expr *left;
	relOp op;
	Expr *right;
};

class LogOp : public Expr
{
public:
	LogOp(logOp o, Expr *l = NULL, Expr *r = NULL) : left(l), op(o), right(r) {}
	~LogOp()
	{
		delete left;
		delete right;
	}

	virtual void sem() override
	{
		switch (op)
		{
		case TRUE:
		case FALSE:
			break;
		case NOT:
			right->type_check(typeBoolean);
			break;
		case AND:
		case OR:
			right->type_check(typeBoolean);
			left->type_check(typeBoolean);
		}
		type = typeBoolean;
	}

private:
	Expr *left;
	logOp op;
	Expr *right;
};