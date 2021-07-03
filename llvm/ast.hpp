#pragma once

#include "llvm/ADT/APFloat.h"
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
#include "codegen.hpp"

#include <memory>
#include <deque>

// using namespace llvm;

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

static llvm::LLVMContext TheContext;
static llvm::IRBuilder<> Builder;
static std::unique_ptr<llvm::Module> TheModule;
static std::map<std::string, llvm::AllocaInst *> NamedValues;

static inline llvm::Constant *c32(int n) {
    return llvm::ConstantInt::get(i32, n);
}

static inline llvm::Constant *c8(unsigned char b) {
    return llvm::ConstantInt::get(i8, b);
}

static llvm::Type *i32 = llvm::Type::getInt32Ty(TheContext);
static llvm::Type *i8 = llvm::Type::getInt8Ty(TheContext);
static llvm::Type *proc = llvm::Type::getVoidTy(TheContext);

static std::deque<ActivationRecord*> activationRecordStack;
static LLVMScope scopes;


// TODO REFERENCES
llvm::Type *translateType(Type type, PassMode mode = PASS_BY_VALUE)
{
	llvm::Type *ret;
	switch (type->dtype)
	{
	case TYPE_INTEGER:
		ret = llvm::Type::getInt32Ty(TheContext);
		break;
	case TYPE_VOID:
		ret = llvm::Type::getVoidTy(TheContext);
		break;
	case TYPE_LIST:
		auto listType = translateType(type->refType);
		auto myStructType = llvm::StructType::create(TheContext, "myStruct"); 
		auto myStructPtrType = llvm::PointerType::get(myStructType, 0); 
		myStructType->setBody({ listType, myStructPtrType }, false); 
		ret = myStructType;
		break;
	case TYPE_IARRAY:
		ret = llvm::ArrayType::get(translateType(type->refType), type->size);
		break;
	}
	if (mode == PASS_BY_REFERENCE)
		ret = ret->getPointerTo();
	return ret;
}


class AST
{
public:
	virtual ~AST() {}
	virtual void sem() {}
	virtual llvm::Value *codegen() = 0;

// protected:
// 	static llvm::LLVMContext TheContext;
// 	static llvm::IRBuilder<> Builder;
// 	static std::unique_ptr<llvm::Module> TheModule;
// 	static std::map<std::string, llvm::AllocaInst *> NamedValues;
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

	virtual llvm::Value *codegen() override
	{
		for (Stmt *s : stmt_list)
			llvm::Value *v = s->codegen();
		return nullptr;
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

	const char *getName()
	{
		return var;
	}

	virtual llvm::Value *codegen() override
	{
		if (activationRecordStack.front()->isRef(var))
		{
			auto *addr = Builder.CreateLoad(activationRecordStack.front()->getAddr(var));
			return Builder.CreateLoad(addr);
		}
		else
			return Builder.CreateLoad(activationRecordStack.front()->getVal(var));

		return nullptr;
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

	std::vector<const char *> get_var_list_names()
	{
		return var_list->getList();
	}

	virtual void passParameters(SymbolEntry *f)
	{
		for (const char *v : var_list->getList())
			newParameter(v, type, mode, f);
	}

	virtual llvm::Value *codegen() override
	{
		for (auto v : var_list->getList())
		{
			activationRecordStack.front()->addArg(v, type, mode);
			activationRecordStack.front()->addVar(v, type, mode);
		}
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

	virtual llvm::Value *codegen() override
	{
		for (auto f : formal_list)
			f->codegen();
	}

	std::vector<Formal *> get_formal_list() 
	{
		return formal_list;
	}

	std::vector<const char *> get_arg_names() 
	{
		std::vector<const char *> ret;
		for(auto f : formal_list)
		{
			for(auto name : f->get_var_list_names())
				ret.push_back(name);
		}
		return ret;
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

	virtual FormalList *getFormalList()
	{
		return this->formal_list;
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

	virtual Type getType()
	{
		return this->type;
	}

	virtual const char *getName()
	{
		return this->functionName;
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

	virtual llvm::Value *codegen() override
	{
		for (Definition *d : definition_list)
			d->codegen();
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

	virtual llvm::Value *codegen() override
	{
		auto newBlock = new ActivationRecord();
		activationRecordStack.push_front(newBlock);
		header->getFormalList()->codegen();
		if (scopes.getFunc(header->getName()) == NULL)
		{
			llvm::FunctionType *ftype = llvm::FunctionType::get(
				translateType(this->header->getType()), activationRecordStack.front()->getArgs(), false);

			llvm::Function *func = llvm::Function::Create(
				ftype, llvm::Function::ExternalLinkage, header->getName(), TheModule.get());

			activationRecordStack.front()->setFunc(func);
			scopes.addFunc(header->getName(), func);
		}
		else 
			activationRecordStack.front()->setFunc(scopes.getFunc(header->getName()));

		scopes.openScope();

		llvm::Function *func = scopes.getFunc(header->getName());

		int index = 0;
		auto var_list = this->header->getFormalList()->get_arg_names();
		for (auto &Arg : func->args())
			Arg.setName(var_list[index++]);

		llvm::BasicBlock *FuncBB = llvm::BasicBlock::Create(TheContext, "entry", func);
		Builder.SetInsertPoint(FuncBB);
		activationRecordStack.front()->setCurrentBlock(FuncBB);
		for (auto &Arg : func->args())
		{
			auto *alloca = Builder.CreateAlloca(Arg.getType(), nullptr, Arg.getName());
			if (Arg.getType()->isPointerTy())
				activationRecordStack.front()->addAddr(Arg.getName(), alloca);
			else
				activationRecordStack.front()->addVal(Arg.getName(), alloca);
			Builder.CreateStore(&Arg, alloca);
		}

		def_list->codegen();
		stmt_list->codegen();

		if (func->getReturnType()->isVoidTy())
			Builder.CreateRetVoid();
		else
		{
			if (!activationRecordStack.front()->hasReturn())
			{
				if (func->getReturnType()->isIntegerTy(32))
					Builder.CreateRet(c32(0));
				else
					Builder.CreateRet(c8(0));
			}
		}

		activationRecordStack.pop_front();
		scopes.closeScope();

		if (!main)
			Builder.SetInsertPoint(activationRecordStack.front()->getCurrentBlock());

		return nullptr;
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

	virtual llvm::Value* codegen()
	{
		auto newBlock = new ActivationRecord();
		activationRecordStack.push_front(newBlock);
		header->getFormalList()->codegen();

		llvm::FunctionType *ftype = llvm::FunctionType::get(
			translateType(header->getType()), activationRecordStack.front()->getArgs(), false);

		llvm::Function *func = llvm::Function::Create(
			ftype, llvm::Function::ExternalLinkage, header->getName(), TheModule.get());

		scopes.addFunc(header->getName(), func);
		activationRecordStack.pop_front();
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

	virtual llvm::Value* codegen() override
	{
		for (const char *varName : var_list->getList())
		{
			auto *llvm_type = translateType(this->type);
			auto *alloca = Builder.CreateAlloca(llvm_type, nullptr, varName);
			
			activationRecordStack.front()->addVar(varName, type);
			activationRecordStack.front()->addVal(varName, alloca);
		}
		return nullptr;
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
			// if expression is not variable and mode is reference error
			e->type_check(paramType);
			args = args->eParameter.next;
		}
		if (argMismatch)
			error("Expected %d arguments for function %s, but %lu were given.", functionArguments, functionName, expr_list->getList().size());
		else if (args)
		{
			while (args)
			{
				++functionArguments;
				args = args->eParameter.next;
			}
			error("Expected %d arguments for function %s, but %lu were given.", functionArguments, functionName, expr_list->getList().size());
		}
	}

	virtual llvm::Value *codegen() override
	{
		llvm::Function *TheFunction = scopes.getFunc(this->functionName);

		std::vector<llvm::Value *> callArgs;

		auto expr_vec = this->expr_list->getList();


		int index = 0;
		for (auto &Arg : TheFunction->args()) {
			/* If argument by reference */
			if (Arg.getType()->isPointerTy()) {
				auto var = std::dynamic_pointer_cast<Var>(this->params[index]);
				/* Found variable */
				if (var) {
					if (var->index == nullptr) {
						if (genBlocks.front()->isRef(var->id)) {
							auto par = Builder.CreateLoad(
								genBlocks.front()->getAddr(var->id));
							callArgs.push_back(par);
						} else {
							llvm::Value *par;
							if (genBlocks.front()->getVar(var->id)->isArrayTy())
								par = Builder.CreateGEP(
									genBlocks.front()->getVal(var->id),
									std::vector<llvm::Value *>{c32(0), c32(0)});
							else
								par = genBlocks.front()->getVal(var->id);
							callArgs.push_back(par);
						}
					} else {
						auto idx = var->index->codegen();
						if (genBlocks.front()->isRef(var->id)) {
							llvm::Value *par = Builder.CreateLoad(
								genBlocks.front()->getAddr(var->id));
							par = Builder.CreateGEP(par, idx);
							callArgs.push_back(par);
						} else {
							llvm::Value *par = genBlocks.front()->getVal(var->id);
							par = Builder.CreateGEP(
								par, std::vector<llvm::Value *>{c32(0), idx});
							callArgs.push_back(par);
						}
					}
					index++;
					continue;
				}
				auto strlit =
					std::dynamic_pointer_cast<ast::String>(this->params[index]);
				/* Found string literal */
				if (strlit) {
					callArgs.push_back(strlit->codegen());
					index++;
					continue;
				}
				linecount = this->line;
				error("Expected variable or string literal");
			} else {
				auto par = this->params[index];
				callArgs.push_back(par->codegen());
				index++;
			}
		}
		return Builder.CreateCall(TheFunction, callArgs);

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

	virtual llvm::Value* codegen() override
	{
		return Builder.CreateGlobalStringPtr(this->str);
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

	virtual llvm::Value* codegen() override
	{
		return llvm::ConstantInt::get(i32, num);
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

	virtual llvm::Value* codegen() override
	{
		return llvm::ConstantInt::get(i8, c);
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

	virtual llvm::Value* codegen() override
	{
		llvm::Value *l;
		llvm::Value *r = right->codegen();
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
	virtual llvm::Value* codegen() override
	{
		llvm::Value *l = left->codegen();
		llvm::Value *r = right->codegen();
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

	virtual llvm::Value* codegen() override
	{
		llvm::Value *l;
		llvm::Value *r;
		if (left != NULL)
			l = left->codegen();
		if (right != NULL)
			r = right->codegen();
		switch (op)
		{
		case TRUE:
			return llvm::ConstantInt::getTrue(TheContext);
		case FALSE:
			return llvm::ConstantInt::getFalse(TheContext);
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

	virtual llvm::Value* codegen() override
	{
		llvm::Value *r = right->codegen();
		llvm::Value *l;
		if (left != NULL)
			l = left->codegen();
		if (op == head)
		{
			r = Builder.CreateGEP(r, 0);
			return Builder.CreateLoad(r);
		}
		else if ( op == tail )
		{
			r = Builder.CreateGEP(r, 1);
			return Builder.CreateLoad(r);
		}
		else if ( op == append )
		{	
			auto *new_head_alloca = Builder.CreateAlloca(r->getType(), nullptr);
			auto *new_head_struct = Builder.CreateLoad(new_head_alloca);

			auto *new_val_address = Builder.CreateGEP(new_head_struct,1);
			Builder.CreateStore(l, new_val_address);

			auto *new_head_next = Builder.CreateGEP(new_head_struct,0);
			Builder.CreateStore(r, new_head_next);
		}
		else if ( op == nil )
		{
			Type t = new Type_tag{
				TYPE_LIST,
				NULL,
				0,
				0
			};
			return llvm::ConstantPointerNull(translateType(t)->getPointerTo());
		}
		else if (  op == nilq )
		{
			if( llvm::ConstantPointerNull::classof(r)) 
				return llvm::ConstantInt::getTrue(TheContext);
			else 
				return llvm::ConstantInt::getFalse(TheContext);
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

	llvm::Value* codegenIndex()
	{
		return index->codegen();
	}

	// virtual llvm::Value* codegen() override
	// {

	// }

private:
	Expr *array;
	Expr *index;
};

class ArrayInit : public Stmt
{
public:
	ArrayInit(const char *v, Type t, Expr *e) : arrayName(v), refT(t), expr(e){};
	~ArrayInit()
	{
		delete arrayName;
		delete type;
		delete refT;
		delete expr;
	}

	virtual void sem() override
	{
		if (refT->dtype != TYPE_INTEGER && refT->dtype != TYPE_BOOLEAN && refT->dtype != TYPE_CHAR)
			error("Arrays of integers, booleans and characters are only supported.");
		
		this->type = typeIArray(refT);
		if (expr->getType()->dtype != TYPE_INTEGER)
			error("Array size must be of type integer.");
	}

	// Sto semantic na koita3oume na tsekaroume oti ikanopoieitai kai to semantic tou assignStmt
	// oti to aristero kommati exei to idio data type me to de3i kommati
	// na ftia3oume parser.y sto 212
	virtual llvm::Value* codegen() override
	{
		auto size = expr->codegen();
		// this->type->size = size;
		auto *arrayType = translateType(this->type);
		auto *alloca = Builder.CreateAlloca(arrayType, size, this->arrayName);
		activationRecordStack.front()->addVar(this->arrayName, this->type);
		activationRecordStack.front()->addVal(this->arrayName, alloca);
		return nullptr;
	}

private:
	Type type;
	const char *arrayName;
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

	virtual llvm::Value* codegen() override
	{
		llvm::Value* rval = right->codegen();
		llvm::Value* lval = left->codegen();

		/* Normal Variable */
		if (std::dynamic_pointer_cast<ArrayIndexing*>(left) == nullptr)
		{
			if (activationRecordStack.front()->isRef(lval->getName()))
			{
				auto *addr = Builder.CreateLoad(activationRecordStack.front()->getAddr(lval->getName()));
				return Builder.CreateStore(rval, addr);
			}
			else
			{
				return Builder.CreateStore(rval, activationRecordStack.front()->getVal(lval->getName()));
			}
		}
		/* Array */
		else
		{
			// std::dynamic_pointer_cast<ArrayIndexing>()
			auto *idx = dynamic_cast<ArrayIndexing*>(left)->codegenIndex();
			llvm::Value *val;
			if (activationRecordStack.front()->isRef(lval->getName()))
			{
				val = Builder.CreateLoad(activationRecordStack.front()->getAddr(lval->getName()));
				val = Builder.CreateGEP(val, idx);
			}
			else
			{
				val = Builder.CreateGEP(activationRecordStack.front()->getVal(lval->getName()), std::vector<llvm::Value *>{c32(0), idx});
			}
			return Builder.CreateStore(rval, val);
		}
		return nullptr;
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
			error("Invalid type of return expression: Expected %s, found %s.", TypeToStr(returnType), TypeToStr(exprType));
	}

	virtual llvm::Value* codegen() override
	{
		activationRecordStack.front()->addRet();
        return Builder.CreateRet(this->returnExpr->codegen());
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

	// TODO while instead of recursive
	// TODO check if setting basic blocks in AR is redundant 
	virtual llvm::Value* codegen() override
	{
		if( cond == NULL && stmt_list != NULL )
			return stmt_list->codegen();

		llvm::Value *CondV = cond->codegen();

		// Convert condition to a bool by comparing non-equal to 0.0.
		CondV = Builder.CreateFCmpONE(CondV, llvm::ConstantFP::get(TheContext, llvm::APFloat(0.0)), "ifcond");

		llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();

		// Create blocks for the then and else cases.  Insert the 'then' block at the
		// end of the function.
		llvm::BasicBlock *ThenBB = llvm::BasicBlock::Create(TheContext, "then", TheFunction);
		llvm::BasicBlock *ElseBB = llvm::BasicBlock::Create(TheContext, "else");
		llvm::BasicBlock *MergeBB = llvm::BasicBlock::Create(TheContext, "ifcont");

		Builder.CreateCondBr(CondV, ThenBB, ElseBB);

		// Emit then value.
		Builder.SetInsertPoint(ThenBB);
		activationRecordStack.front()->setCurrentBlock(ThenBB);

		stmt_list->codegen();
		if (!activationRecordStack.front()->hasReturn())
        	Builder.CreateBr(MergeBB);

		// Emit else block.
		TheFunction->getBasicBlockList().push_back(ElseBB);
		Builder.SetInsertPoint(ElseBB);
		activationRecordStack.front()->setCurrentBlock(ElseBB);

		if( nextIf != nullptr )
			nextIf->codegen();
		if (!activationRecordStack.front()->hasReturn())
        	Builder.CreateBr(MergeBB);

		// Emit merge block.
		TheFunction->getBasicBlockList().push_back(MergeBB);
		Builder.SetInsertPoint(MergeBB);
		activationRecordStack.front()->setCurrentBlock(MergeBB);

		return nullptr;
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

	virtual llvm::Value* codegen() override
	{
		initializers->codegen();

		llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
		llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(TheContext, "loop", TheFunction);
		llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(TheContext, "after");

		llvm::Value *CondV = threshold->codegen();
		if (!CondV)
			return nullptr;

		// Convert condition to a bool by comparing non-equal to 0.0.
		CondV = Builder.CreateFCmpONE(CondV, llvm::ConstantFP::get(TheContext, llvm::APFloat(0.0)), "loopcond");

		Builder.CreateCondBr(CondV, LoopBB, AfterBB);

		// Start insertion in LoopBB.
		Builder.SetInsertPoint(LoopBB);
		activationRecordStack.front()->setCurrentBlock(LoopBB);

		loop_body->codegen();

		// Emit the step value.
		steps->codegen();

		llvm::Value *CondV = threshold->codegen();
		if (!CondV)
			return nullptr;

		// Convert condition to a bool by comparing non-equal to 0.0.
		CondV = Builder.CreateFCmpONE(CondV, llvm::ConstantFP::get(TheContext, llvm::APFloat(0.0)), "loopcond");

		// Insert the conditional branch into the end of LoopEndBB.
		Builder.CreateCondBr(CondV, LoopBB, AfterBB);

		// Any new code will be inserted in AfterBB.
		TheFunction->getBasicBlockList().push_back(AfterBB);
		Builder.SetInsertPoint(AfterBB);
		activationRecordStack.front()->setCurrentBlock(AfterBB);

		return nullptr;
	}

private:
	Stmt *initializers;
	Expr *threshold;
	Stmt *steps;
	StmtList *loop_body;
};























