#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

/********************************************************************
			HEY! CHECK OUT THE "SEM COMPLETED" SECTION!
 ********************************************************************/

enum relOp { eq, lt, gt, le, ge, neq };

enum logOp { AND, OR, NOT, TRUE, FALSE };

enum listOp { nil, nilq, head, tail, append };

typedef enum HeaderType { Func_Decl, Func_Def } HeaderType;

inline std::ostream &operator<<(std::ostream &out, const AST &t)
{
	t.printOn(out);
	return out;
}



class Stmt : public AST
{
public:
	//virtual void run() const = 0;
};

class ExitStmt : public Stmt
{
public:
	ExitStmt() {}
	~ExitStmt() {}
	virtual void printOn(std::ostream &out) const override
	{
		out << "Exit";
	}
};

class ReturnStmt : public Stmt
{
public:
	ReturnStmt(Expr *e) : returnExpr(e) {}
	~ReturnStmt() {}
	virtual void printOn(std::ostream &out) const override
	{
		out << "Return";
	}

private:
	Expr *returnExpr;
};

class SkipStmt : public Stmt
{
public:
	SkipStmt() {}
	~SkipStmt() {}
	virtual void printOn(std::ostream &out) const override
	{
		out << "Skip";
	}
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
	virtual void printOn(std::ostream &out) const override
	{
		out << op << "(" << *left << ", " << *right << ")";
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

	virtual void printOn(std::ostream &out) const override
	{
		out << "StmtList(";
		bool first = true;
		for (Stmt *s : stmt_list)
		{
			if (!first)
				out << ", ";
			first = false;
			out << *s;
		}
		out << ")";
	}

private:
	std::vector<Stmt *> stmt_list;
};

class For : public Stmt
{
public:
	For( StmtList *s1 ,Expr *e, StmtList *s2 , StmtList *s3) : 
	initializers(s1) , threshold(e) , steps(s2) , loop_body(s3) {}
	~For()
	{
		delete threshold;
		delete initializers;
		delete steps;
		delete loop_body;
	}
	virtual void printOn(std::ostream &out) const override
	{
		//out << "For(" << *initializers << ", " << *threshold << ", " *steps << ": " << *loop_body << ")";
	}

private:
	Expr *threshold;
	Stmt *initializers;
	Stmt *steps;
	Stmt *loop_body;
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
	virtual void printOn(std::ostream &out) const override
	{
		//out << "If(" << *cond << ", " << stmt_list->printOn(out) << ")";
	}
	void append(If *i){	nextIf = i;	}

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
	virtual void printOn(std::ostream &out) const override
	{
		out << "(" << *array << ", " << *index << ")";
	}

private:
	Expr *array;
	Expr *index;
};

class ArrayInit : public Expr
{
public:
	ArrayInit(std::string *t , Expr *e) : type(t) , expr(e) {};
	~ArrayInit()
	{
		delete type;
		delete expr;
	}
	virtual void printOn(std::ostream &out) const override
	{
		out << type ;
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
	virtual void printOn(std::ostream &out) const = 0;
	virtual void sem () {}
};

class Expr : public AST
{
public:
	//virtual int eval() const = 0;
	void type_check(Type t) {
		sem();
		if (!equalType(t, type)) 
			error("Invalid type of operand. Expected %s, got %s.", TypeToStr(t), TypeToStr(type));
	}

	Type get_type () {
		sem();
		return type;
	}

	virtual void lvalue_error () {}
protected:
	Type type;
};

class Var : public Expr
{
public:
	Var(const char * v) : var(v){}
	virtual void printOn(std::ostream &out) const override
	{
		out << "Id(" << type << " " << var << ")";
	}

	virtual void sem () override {
		SymbolEntry * e = lookupEntry(var, LOOKUP_ALL_SCOPES, true);
		type = e->u.eVariable.type;
	}
private:
	const char *var;
};

class VarList : public Expr
{
public:
	std::vector<const char *> var_list;
	
	VarList(const char *v)	{ var_list.push_back(v); }
	
	void append(const char *v)	{ var_list.push_back(v); }

	virtual void printOn(std::ostream &out) const override
	{
		//out << "Id(" << type << " " << var << ")";
	}
};

class Formal : public AST
{
public:
	Formal(Type t, VarList *v, bool isRef=false) : type(t) , var_l(v) {
		if(isRef)
			mode = PASS_BY_REFERENCE;
		else
			mode = PASS_BY_VALUE;
	}
	~Formal() {
		delete var_list; 
	}

	virtual void printOn(std::ostream &out) const override
	{
		
	}

	virtual void passParameters (SymbolEntry *f) {
		for (const char *v : var_l->var_list)
			SymbolEntry *e = newParameter(v, type, mode, f);
	}

private:
	Type type;
	VarList *var_l;
	PassMode mode;
};

class FormalList : public AST
{
public:
	FormalList() {}
	~FormalList() {}

	void append(Formal *f){	formal_list.push_back(f); }

	virtual void printOn(std::ostream &out) const override
	{
		
	}

	virtual void passParameters (SymbolEntry *f) {
		for(Formal *f : formal_list) f->passParameters(f);
	}

private:
	std::vector<Formal *> formal_list;
};

class Header : public AST
{
public:
	Header(const char *v, FormalList *fl, Type t, HeaderType D) : 
	functionName(v), formal_list(fl) , type(t), T(D) {} 
	~Header()
	{
		delete functionName;
		delete formal_list;
		delete type;
	}

	virtual void printOn(std::ostream &out) const override
	{
		
	}

	virtual void sem () override {
		/* newFunction performs check for duplicate declaration in the same scope */
		SymbolEntry * f = newFunction(functionName);
		if(!T)		/* Declarations should be forwarded */
			forwardFunction(f);
		openScope();
		formal_list->passParameters(f);
		endFunctionHeader(f, type);
		closeScope();                           /* check scopes here !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! */
	}

private:
	const char *functionName;
	FormalList *formal_list;
	Type type;
	HeaderType T;
};

class Definition : public AST {
};

class DefinitionList : public AST
{
public:
	DefinitionList() : definition_list() {}
	~DefinitionList(){}

	void append(Definition *d){	definition_list.push_back(d); }


	virtual void printOn(std::ostream &out) const override
	{
		
	}

	virtual void sem() override{
		for (Definition *d : definition_list) d->sem();
	}
private:
	std::vector<Definition *> definition_list;
};

class FunctionDefinition : public Definition
{
public:
	FunctionDefinition(Header *h,DefinitionList *dl=NULL, StmtList *sl=NULL) : header(h), def_list(dl), stmt_list(sl) {} 
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

	virtual void printOn(std::ostream &out) const override
	{
		
	}

	virtual void sem () override {
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

	virtual void printOn(std::ostream &out) const override
	{
		
	}

	virtual void sem () override {
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
	~VarDefinition() {
		delete var_list; 
		delete type;
	}

	virtual void printOn(std::ostream &out) const override
	{
		
	}

	virtual void sem() override {
		for (const char * variable : var_l->var_list)
			SymbolEntry * e = newVariable(variable, type);
	}

private:
	Type type;
	VarList *var_l;
};

class ExprList : public Expr
{
public:
	std::vector<Expr *> expr_list;

	ExprList() : expr_list() {}
	~ExprList()	{
		for (Expr *e : expr_list)
			delete e;
	}
	void append(Expr *e) { expr_list.push_back(e); }

	virtual void printOn(std::ostream &out) const override
	{
		
	}
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
	virtual void printOn(std::ostream &out) const override
	{
		out << "(" << *functionName << ", " << *expr_list << ")";
	}

	virtual void sem () override {
		int functionArguments = 0;
		bool argMismatch = false;
		SymbolEntry *f = lookupEntry(functionName);
		if(f->u.eFunction.isForward)
			error("Function %s declared but not defined.", functionName);
		type = f->u.eFunction.resultType;
		SymbolEntry * args;
		args = f->u.eFunction.firstArgument;
		for(Expr *e : expr_l->expr_list){
			Type paramType; 
			if(args){
				++functionArguments;
				paramType = args->u.eParameter.type;
			}
			else{
				argMismatch = true;
				break;
			}
			e->type_check(paramType);
			args = args->u.eParameter.next; 
		}
		if (argMismatch)
			error("Expected %d arguments for function %s, but %lu were given.", 
				   functionArguments, functionName, expr_l->expr_list.size());
		else if (args){
			while (args){
				++functionArguments;
				args = args->u.eParameter.next;
			}
			error("Expected %d arguments for function %s, but %lu were given.", 
				   functionArguments, functionName, expr_l->expr_list.size());
		}
	}

	virtual void lvalue_error () override {
		error("Lvalue cannot be a function call.");
	}

private:
	const char *functionName;
	ExprList *expr_l;
};

class ConstString : public Expr {
public:
	ConstString(const char * str) : str(str) {}
	virtual void printOn(std::ostream &out) const override
	{
		out << "Const(" << str << ")";
	}

	virtual void sem () override {
		type = typeIArray(typeChar);
	}

	virtual void lvalue_error () override {
		error("Lvalue cannot be a string literal.");
	}

private:
	const char * str;
};

class ConstInt : public Expr {
public:
	ConstInt(int n) : num(n) {}
	
	virtual void printOn(std::ostream &out) const override
	{
		out << "Const(" << num << ")";
	}

	virtual void sem () override {
		type = typeInteger;
	}

private:
	int num;
};

class AssignStmt : public Stmt {
public:
	AssignStmt(Expr *l, Expr *r) : left(l), right(r) {}
	~AssignStmt()
	{
		delete left;
		delete right;
	}
	virtual void printOn(std::ostream &out) const override
	{
		//out << "If(" << *cond << ", " << stmt_list->printOn(out) << ")";
	}

	virtual void sem () override {
		left->lvalue_error();
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
	virtual void printOn(std::ostream &out) const override
	{
		out << op << "(" << *left << ", " << *right << ")";
	}

	virtual void sem () override {
		right->type_check(typeInteger);
		if(left)
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
	virtual void printOn(std::ostream &out) const override
	{
		out << op << "(" << *left << ", " << *right << ")";
	}

	virtual void sem () override {
		Type leftType = left->get_type();
		Type rightType = right->get_type();
		if(!equalType(leftType, rightType))
			error("Operands of comparison have different types: %s and %s.", 
				   TypeToStr(leftType). TypeToStr(rightType));
		if(leftType->kind == TYPE_INTEGER 
		   or leftType->kind == TYPE_BOOLEAN
		   or leftType->kind == TYPE_CHAR)
			type = typeBoolean;
			return;
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
	virtual void printOn(std::ostream &out) const override
	{
		out << op << "(" << *left << ", " << *right << ")";
	}

	virtual void sem () override {
		switch(op) {
			case TRUE: case FALSE:
				break;
			case NOT:
				right->type_check(typeBoolean);
				break;
			case AND: case OR:
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