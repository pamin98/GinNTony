#pragma once

#include "llvm-9/llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "symbol.hpp"
#include "error.hpp"

using namespace llvm;

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

enum HeaderType
{
	Func_Decl,
	Func_Def
};

/// CreateEntryBlockAlloca - Create an alloca instruction in the entry block of
/// the function.  This is used for mutable variables etc.
static AllocaInst *CreateEntryBlockAlloca(Function *TheFunction,const std::string &VarName) 
{
	IRBuilder<> TmpB(&TheFunction->getEntryBlock(),TheFunction->getEntryBlock().begin());
	return TmpB.CreateAlloca(Type::getDoubleTy(getGlobalContext()), 0, VarName.c_str());
}

class AST
{
public:
	virtual ~AST() {}
	virtual void sem() {}
	virtual Value *codegen() = 0;

protected:
	static LLVMContext TheContext;
	static IRBuilder<> Builder;
	static std::unique_ptr<Module> TheModule;
	static std::map<std::string, AllocaInst *> NamedValues;

	static Type *i8;
	static Type *i32;
	static Type *i64;
};

class Expr : public AST
{
public:
	void type_check(Type t)
	{
		if (type == NULL)
			sem();
		if (!equalType(t, type))
			error("Invalid type of operand. Expected %s, found %s.", TypeToStr(t), TypeToStr(type));
	}

	Type getType()
	{
		if (type == NULL)
			sem();
		return type;
	}

	virtual void checkLVal() {}

protected:
	Type type;
};

class Stmt : public AST
{
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

	virtual void sem() override
	{
		for (Stmt *s : stmt_list)
			s->sem();
	}

	virtual Value *codegen() override
	{
		for (Stmt *s : stmt_list)
			Value *v = s->codegen();
		return NULL;
	}

private:
	std::vector<Stmt *> stmt_list;
};

class Var : public Expr
{
public:
	Var(const char *v) : var(v) {}

	virtual void sem() override
	{
		SymbolEntry *e = lookupEntry(var, LOOKUP_ALL_SCOPES, true);
		if (e->entryType == ENTRY_FUNCTION)
			error("%s is a function, expected parenthesis", e->id);
		type = e->eVariable.type;
	}

	const char * getName()
	{
		return var;
	}

	virtual Value *codegen() override
	{
		// Look this variable up in the function.
		Value *V = NamedValues[var];
		if (V == 0) return ErrorV("Unknown variable name");

		// Load the value.
		return Builder.CreateLoad(V, var);
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
			newParameter(v, type, mode, f);
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
		for (Formal *formal : formal_list)
			formal->passParameters(f);
	}

private:
	std::vector<Formal *> formal_list;
};

class Header : public AST
{
public:
	Header(const char *v, FormalList *fl, Type t, HeaderType D) : functionName(v), formal_list(fl), type(t), header_type(D) {}
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
		if (header_type == Func_Decl) /* Declarations should be forwarded */
			declareFunction(f);
		openScope();
		formal_list->passParameters(f);
		endFunctionHeader(f, type);
	}

private:
	const char *functionName;
	FormalList *formal_list;
	Type type;
	HeaderType header_type;
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
			newVariable(variable, type);
	}

	virtual Value *codegen() override
	{
		Function *TheFunction = Builder.GetInsertBlock()->getParent();
		for (const char *v : var_list->getList())
		{
			//TODO Nested Functions, Var Type
			AllocaInst *Alloca = CreateEntryBlockAlloca(TheFunction, v);
			NamedValues[v] = Alloca;
		}
		return NULL;
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
		SymbolEntry *f = lookupEntry(functionName, LOOKUP_ALL_SCOPES, true);
		type = f->eFunction.resultType;
		SymbolEntry *args;
		args = f->eFunction.firstArgument;
		for (Expr *e : expr_list->getList())
		{
			Type paramType;
			if (args)
			{
				++functionArguments;
				paramType = args->eParameter.type;
			}
			else
			{
				argMismatch = true;
				break;
			}
			e->type_check(paramType);
			args = args->eParameter.next;
		}
		if (argMismatch)
			error("Expected %d arguments for function %s, but %lu were given.",
				  functionArguments, functionName, expr_list->getList().size());
		else if (args)
		{
			while (args)
			{
				++functionArguments;
				args = args->eParameter.next;
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

class ConstChar : public Expr
{
public:
	ConstChar(char c) : c(c) {}

	virtual void sem() override
	{
		type = typeChar;
	}

private:
	char c;
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
		if (left != NULL)
			left->type_check(typeInteger);
		type = typeInteger;
	}

	virtual Value *codegen() override
	{
		Value *l;
		Value *r = right->codegen();
		if (left != NULL)
			l = left->codegen();
		switch (op)
		{
		case '+':
			if (left == NULL)
				return r;
			return Builder.CreateAdd(l, r, "addtmp");
		case '-':
			if (left == NULL)
				return Builder.CreateNeg(r, "negtmp");
			return Builder.CreateSub(l, r, "subtmp");
		case '*':
			return Builder.CreateMul(l, r, "multmp");
		case '/':
			return Builder.CreateSDiv(l, r, "divtmp");
		case '%':
			return Builder.CreateSRem(l, r, "modtmp");
		}
		return NULL;
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
		Type leftType = left->getType();
		Type rightType = right->getType();
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

	// TODO
	/* Add sign extensions ?? */
	virtual Value *codegen() override
	{
		Value *l = left->codegen();
		Value *r = right->codegen();
		// if(leftType->dtype == TYPE_BOOLEAN)
		// {
		// 	switch(op)
		// 	{
		// 		case gt:  return Builder.CreateICmpUGT(l, r, "gtcheck");
		// 		case lt:  return Builder.CreateICmpULT(l, r, "ltcheck");
		// 		case ge:  return Builder.CreateICmpUGE(l, r, "gecheck");
		// 		case le:  return Builder.CreateICmpULE(l, r, "lecheck");
		// 	}
		// }
		switch (op)
		{
			case eq:
				return Builder.CreateICmpEQ(l, r, "eqcheck");
			case neq:
				return Builder.CreateICmpNE(l, r, "neqcheck");
			case gt:
				return Builder.CreateICmpSGT(l, r, "gtcheck");
			case lt:
				return Builder.CreateICmpSLT(l, r, "ltcheck");
			case ge:
				return Builder.CreateICmpSGE(l, r, "gecheck");
			case le:
				return Builder.CreateICmpSLE(l, r, "lecheck");
		}
		return NULL;
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

	virtual Value *compile() override
	{
		Value *l;
		Value *r;
		if (left != NULL)
			l = left->compile();
		if (right != NULL)
			r = right->compile();
		switch (op)
		{
		case TRUE:
			return ConstantInt::getTrue(TheContext);
		case FALSE:
			return ConstantInt::getFalse(TheContext);
		case NOT:
			return Builder.CreateNot(r, "nottmp");
		case AND:
			return Builder.CreateAnd(l, r, "andtmp");
		case OR:
			return Builder.CreateOr(l, r, "ortmp");
		}
		return NULL;
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

	virtual void sem() override
	{
		switch (op)
		{
		case nil:
			type = typeNil;
			break;
		case head:
			if (right->getType()->dtype != TYPE_LIST)
				error("Expected list, found %s.", TypeToStr(right->getType()));
			type = right->getType()->refType;
			break;
		case tail:
			if (right->getType()->dtype != TYPE_LIST)
				error("Expected list, found %s.", TypeToStr(right->getType()));
			type = right->getType();
			break;
		case nilq:
			if (right->getType()->dtype != TYPE_LIST && right->getType()->dtype != TYPE_NIL)
				error("Expected list, found %s.", TypeToStr(right->getType()));
			type = typeBoolean;
			break;
		case append:
			if (right->getType()->dtype == TYPE_NIL)
			{
				type = typeList(left->getType());
				break;
			}
			else if (!equalType(left->getType(), right->getType()->refType))
			{
				error("Cannot append %s to %s.", TypeToStr(left->getType()), TypeToStr(right->getType()));
			}
			type = right->getType();
		}
	}

private:
	Expr *left;
	listOp op;
	Expr *right;
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

	virtual void sem() override
	{
		if (index->getType()->dtype != TYPE_INTEGER)
			error("Array index must be of type integer.");
		if (array->getType()->dtype != TYPE_IARRAY)
			error("Expected array, found %s", TypeToStr(array->getType()));

		type = array->getType()->refType;
	}

private:
	Expr *array;
	Expr *index;
};

class ArrayInit : public Expr
{
public:
	ArrayInit(Type t, Expr *e) : refT(t), expr(e){};
	~ArrayInit()
	{
		delete type;
		delete refT;
		delete expr;
	}

	virtual void sem() override
	{
		if (refT->dtype != TYPE_INTEGER && refT->dtype != TYPE_BOOLEAN && refT->dtype != TYPE_CHAR)
			error("Arrays of integers, booleans and characters are only supported.");

		type = typeIArray(refT);
		if (expr->getType()->dtype != TYPE_INTEGER)
			error("Array size must be of type integer.");
	}

private:
	Type refT;
	Expr *expr;
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
		Type ltype = left->getType();
		right->type_check(ltype);
	}

	virtual Value *codegen() override
	{
		Value *Val = right->codegen();
		if (Val == 0) return 0;

		// Look up the name.
		// TODO Na doume ti paizei ma array indexes
		Value *Variable = NamedValues[left->getName()];
		if (Variable == 0) return ErrorV("Unknown variable name");

		Builder.CreateStore(Val, Variable);
		return Val;
	}

private:
	Expr *left;
	Expr *right;
};

class ExitStmt : public Stmt
{
public:
	ExitStmt() {}
	~ExitStmt() {}

	virtual void sem()
	{
		Type returnType = currentScope->returnType;
		if (!equalType(returnType, typeVoid))
			error("Exit called in non-void function.");
	}
};

class ReturnStmt : public Stmt
{
public:
	ReturnStmt(Expr *e) : returnExpr(e) {}
	~ReturnStmt() {}

	virtual void sem()
	{
		Type returnType = currentScope->returnType;
		Type exprType = returnExpr->getType();
		if (!equalType(exprType, returnType))
			error("Invalid type of return expression: Expected %s, found %s.",
				  TypeToStr(returnType), TypeToStr(exprType));
	}

private:
	Expr *returnExpr;
};

class SkipStmt : public Stmt
{
public:
	SkipStmt() {}
	~SkipStmt() {}
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

	virtual void sem() override
	{
		if (cond != NULL)
		{
			cond->type_check(typeBoolean);
		}
		stmt_list->sem();
		if (nextIf != NULL)
			nextIf->sem();
	}

	virtual Value *codegen() override
	{
		Value *CondV = cond->codegen();
		if (!CondV)
			return nullptr;

		// Convert condition to a bool by comparing non-equal to 0.0.
		CondV = Builder.CreateFCmpONE(CondV, ConstantFP::get(TheContext, APFloat(0.0)), "ifcond");

		Function *TheFunction = Builder.GetInsertBlock()->getParent();

		// Create blocks for the then and else cases.  Insert the 'then' block at the
		// end of the function.
		BasicBlock *ThenBB = BasicBlock::Create(TheContext, "then", TheFunction);
		BasicBlock *ElseBB = BasicBlock::Create(TheContext, "else");
		BasicBlock *MergeBB = BasicBlock::Create(TheContext, "ifcont");

		Builder.CreateCondBr(CondV, ThenBB, ElseBB);

		// Emit then value.
		Builder.SetInsertPoint(ThenBB);

		Value *ThenV = Then->codegen();
		if (!ThenV)
			return nullptr;

		Builder.CreateBr(MergeBB);
		// Codegen of 'Then' can change the current block, update ThenBB for the PHI.
		ThenBB = Builder.GetInsertBlock();

		// Emit else block.
		TheFunction->getBasicBlockList().push_back(ElseBB);
		Builder.SetInsertPoint(ElseBB);

		Value *ElseV = Else->codegen();
		if (!ElseV)
			return nullptr;

		Builder.CreateBr(MergeBB);
		// codegen of 'Else' can change the current block, update ElseBB for the PHI.
		ElseBB = Builder.GetInsertBlock();

		// Emit merge block.
		TheFunction->getBasicBlockList().push_back(MergeBB);
		Builder.SetInsertPoint(MergeBB);
		PHINode *PN = Builder.CreatePHI(Type::getDoubleTy(TheContext), 2, "iftmp");

		PN->addIncoming(ThenV, ThenBB);
		PN->addIncoming(ElseV, ElseBB);
		return PN;
	}

private:
	Expr *cond;
	StmtList *stmt_list;
	If *nextIf;
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

	virtual void sem() override
	{
		initializers->sem();
		threshold->type_check(typeBoolean);
		steps->sem();
		loop_body->sem();
	}

private:
	Stmt *initializers;
	Expr *threshold;
	Stmt *steps;
	StmtList *loop_body;
};