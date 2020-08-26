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
		out << "Shqip";
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

class Const : public Expr
{
public:
	Const(int n) : num(n) {}
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

class varDefinition : public Stmt
{
public:
	varDefinition(std::string t, std::string v, Expr *e) : type(t), var(v), expr(e) {}
	~varDefinition() { delete expr; }
	virtual void printOn(std::ostream &out) const override
	{
		out << "Let(" << var << " = " << *expr << ")";
	}

private:
	std::string type;
	std::string var;
	Expr *expr;
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
	For( StmtList *s1 ,Expr *e, StmtList *s2 , StmtList *s3) : stmt_list1(s1) , expr(e) , stmt_list2(s2) , stmt_list3(s3) {}
	~For()
	{
		delete expr;
		delete stmt_list1;
		delete stmt_list2;
		delete stmt_list3;
	}
	virtual void printOn(std::ostream &out) const override
	{
		//out << "For(" << *expr << ", " << *stmt_list << ")";
	}

private:
	Expr *expr;
	Stmt *stmt_list1;
	Stmt *stmt_list2;
	Stmt *stmt_list3;
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
	void reverse() { std::reverse(expr_list.begin(), expr_list.end()); }
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
	void append(If *i)
	{
		nextIf = i;
	}

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

class Type : public std::string
{
public:
	Type(const char *c): std::string(c) {}
// public:
// 	Type(std::string t) : type(t) {};
// 	~Type();
	
// private:
// 	std::string type;
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

