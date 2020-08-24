#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <string>

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
	virtual int eval() const = 0;
};

class Stmt : public AST
{
public:
	virtual void run() const = 0;
};

extern std::map<std::string, int> globals;

class Id : public Expr
{
public:
	Id(std::string v) : var(v) {}
	virtual void printOn(std::ostream &out) const override
	{
		out << "Id(" << var << ")";
	}
	virtual int eval() const override
	{
		return globals[var];
	}

private:
	std::string var;
};

class Const : public Expr
{
public:
	Const(int n) : num(n) {}
	virtual void printOn(std::ostream &out) const override
	{
		out << "Const(" << num << ")";
	}
	virtual int eval() const override
	{
		return num;
	}

private:
	int num;
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
	virtual int eval() const override
	{
		switch (op)
		{
		case '+':
			return left->eval() + right->eval();
		case '-':
			return left->eval() - right->eval();
		case '*':
			return left->eval() * right->eval();
		case '/':
			return left->eval() / right->eval();
		case '%':
			return left->eval() % right->eval();
		}
		return 0; // this will never be reached.
	}

private:
	Expr *left;
	char op;
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
	virtual void run() const override
	{
		globals[var] = expr->eval();
	}

private:
	std::string type;
	std::string var;
	Expr *expr;
};


class If : public Stmt
{
public:
	If(Expr *c, Stmt *s1,pinaka) : cond(c), stmt1(s1) {}
	~If()
	{
		delete cond;
		delete stmt1;
	}
	virtual void printOn(std::ostream &out) const override
	{
		out << "If(" << *cond << ", " << *stmt1;
		if (stmt2 != nullptr)
			out << ", " << *stmt2;
		out << ")";
	}
	virtual void run() const override
	{
		if (cond->eval())
			stmt1->run();
	}

private:
	Expr *cond;
	Stmt *stmt1;
	Stmt *stmt2;
};

class For : public Stmt
{
public:
	For(Expr *e, Stmt *s) : expr(e), stmt(s) {}
	~For()
	{
		delete expr;
		delete stmt;
	}
	virtual void printOn(std::ostream &out) const override
	{
		out << "For(" << *expr << ", " << *stmt << ")";
	}
	virtual void run() const override
	{
		for (int times = expr->eval(), i = 0; i < times; ++i)
			stmt->run();
	}
private:
	Expr *expr;
	Stmt *stmt;
};

class Block : public Stmt
{
public:
	Block() : stmt_list() {}
	~Block()
	{
		for (Stmt *s : stmt_list)
			delete s;
	}
	void append(Stmt *s) { stmt_list.push_back(s); }
	virtual void printOn(std::ostream &out) const override
	{
		out << "Block(";
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
	virtual void run() const override
	{
		for (Stmt *s : stmt_list)
			s->run();
	}

private:
	std::vector<Stmt *> stmt_list;
};