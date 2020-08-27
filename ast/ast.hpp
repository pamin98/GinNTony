#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

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

class AST
{
public:
	virtual ~AST() {}
	virtual void printOn(std::ostream &out) const = 0;
};

inline std::ostream &operator<<(std::ostream &out, const AST &t)
{
	t.printOn(out);
	return out;
}

class Expr : public AST
{
public:
	//virtual int eval() const = 0;
};

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

extern std::map<std::string, int> globals;

class Var : public Expr
{
public:
	Var(std::string v, std::string t) : var(v), type(t) {}
	virtual void printOn(std::ostream &out) const override
	{
		out << "Id(" << type << " " << var << ")";
	}

private:
	std::string var;
	std::string type;
};

class VarList : public Expr
{
public:
	VarList(Var *v)	{ var_list.push_back(v); }
	
	void append(Var *v)	{ var_list.push_back(v); }

	virtual void printOn(std::ostream &out) const override
	{
		//out << "Id(" << type << " " << var << ")";
	}

private:
	std::vector<Var *> var_list; 
};

class ConstInt : public Expr
{
public:
	ConstInt(int n) : num(n) {}
	virtual void printOn(std::ostream &out) const override
	{
		out << "Const(" << num << ")";
	}

private:
	int num;
};

class ConstString : public Expr
{
public:
	ConstString(std::string str) : str(str) {}
	virtual void printOn(std::ostream &out) const override
	{
		out << "Const(" << str << ")";
	}

private:
	std::string str;
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

private:
	Expr *left;
	logOp op;
	Expr *right;
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
		//out << "For(" << *expr << ", " << *stmt_list << ")";
	}

private:
	Expr *threshold;
	Stmt *initializers;
	Stmt *steps;
	Stmt *loop_body;
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
	void append(Expr *e) { expr_list.push_back(e); }

	virtual void printOn(std::ostream &out) const override
	{
		out << "ExprList(";
		bool first = true;
		for (Expr *e : expr_list)
		{
			if (!first)
				out << ", ";
			first = false;
			out << *e;
		}
		out << ")";
	}

private:
	std::vector<Expr *> expr_list;
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

class CallObject : public Expr, public Stmt
{
public:
	CallObject(Var *n, ExprList *e) : functionName(n), expr_list(e) {}
	~CallObject()
	{
		delete functionName;
		delete expr_list;
	}
	virtual void printOn(std::ostream &out) const override
	{
		out << "(" << *functionName << ", " << *expr_list << ")";
	}

private:
	Var *functionName;
	ExprList *expr_list;
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
	virtual void printOn(std::ostream &out) const override
	{
		//out << "If(" << *cond << ", " << stmt_list->printOn(out) << ")";
	}

private:
	Expr *left;
	Expr *right;
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



class Formal : public AST
{
public:
	Formal(std::string *t, VarList *v, bool isRef=false) : type(t) , var_list(v), isRef(isRef) {}
	~Formal() 
	{
		delete var_list; 
		delete type;
	}

private:
	std::string *type;
	VarList *var_list;
	bool isRef;
};

class FormalList : public AST
{
public:
	FormalList() {}
	~FormalList() {}

	void append(Formal *f){	formal_list.push_back(f); }

private:
	std::vector<Formal *> formal_list;
};


class Function : public AST
{
public:
	Function(Var *v,FormalList *fl,std::string *t=NULL) : functionName(v), formal_list(fl) , type(t) {} 
	~Function()
	{
		delete functionName;
		delete formal_list;
		delete type;
	}
private:
	Var *functionName;
	FormalList *formal_list;
	std::string *type;
};

class Definition : public AST
{

};


class VarDefinition : public Definition
{
public:
	VarDefinition(std::string *t, VarList *v) : type(t), var_list(v) {}
	~VarDefinition() 
	{
		delete var_list; 
		delete type;
	}

private:
	std::string *type;
	VarList *var_list;
};


class DefinitionList : public AST
{
public:
	DefinitionList() : definition_list() {}
	~DefinitionList(){}

	void append(Definition *d){	definition_list.push_back(d); }

private:
	std::vector<Definition *> definition_list;
};

class Header : public AST
{
public:
	Header(Var *v,FormalList *fl,std::string *t=NULL) : functionName(v), formal_list(fl) , type(t) {} 
	~Header()
	{
		delete functionName;
		delete formal_list;
		delete type;
	}
private:
	Var *functionName;
	FormalList *formal_list;
	std::string *type;
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
private:
	Header *header;
};