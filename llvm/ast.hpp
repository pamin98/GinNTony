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
#include "llvm/Bitcode/BitcodeWriter.h"
#include "llvm/Support/FileSystem.h"

#include "llvm/Transforms/IPO/DeadArgumentElimination.h"


#include "llvm/IR/LegacyPassManager.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <typeinfo>

#include "symbol.hpp"
#include "error.hpp"
#include "codegen.hpp"


#include <memory>
#include <deque>

#include <iostream>
#include <ctime>
#include <unistd.h>

static void codegenLibs();

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
static llvm::IRBuilder<> Builder(TheContext);
static std::unique_ptr<llvm::Module> TheModule;
static std::map<std::string, llvm::AllocaInst *> NamedValues;
static std::unique_ptr<llvm::legacy::FunctionPassManager> TheFPM;
static llvm::Function *TheInit;
static llvm::Function *TheMalloc;

static llvm::Type *i32 = llvm::Type::getInt32Ty(TheContext);
static llvm::Type *i8 = llvm::Type::getInt8Ty(TheContext);
static llvm::Type *i1 = llvm::Type::getInt1Ty(TheContext);
static llvm::Type *proc = llvm::Type::getVoidTy(TheContext);


static inline llvm::Constant *c32(int n)
{
	return llvm::ConstantInt::get(i32, n);
}

static inline llvm::Constant *c8(unsigned char b)
{
	return llvm::ConstantInt::get(i8, b);
}

static inline llvm::Constant *c1(int n)
{
	return llvm::ConstantInt::get(i1,n);
}

static std::deque<ActivationRecord *> activationRecordStack;
static LLVMScope scopes;


inline llvm::Type *translateType(Type type, PassMode mode = PASS_BY_VALUE)
{
	llvm::Type *ret;
	switch (type->dtype)
	{
	case TYPE_INTEGER:
	{
		ret = llvm::Type::getInt32Ty(TheContext);
		break;
	}
	case TYPE_BOOLEAN:
	{
		ret = llvm::Type::getInt1Ty(TheContext);
		break;
	}
	case TYPE_CHAR:
	{
		ret = llvm::Type::getInt8Ty(TheContext);
		break;
	}
	case TYPE_VOID:
	{
		ret = llvm::Type::getVoidTy(TheContext);
		break;
	}
	case TYPE_LIST:
	{
		auto listType = translateType(type->refType);
		// auto myStructType = llvm::StructType::create(TheContext, "myStruct");
		auto myStructType = llvm::StructType::create(TheContext);
		auto myStructPtrType = llvm::PointerType::get(myStructType, 0);
		myStructType->setBody({listType, myStructPtrType}, false);
		// ret = myStructType;
		ret = myStructType->getPointerTo();
		break;
	}
	case TYPE_IARRAY:
	{
		if( type->size == 0 )
		{
			ret = translateType(type->refType)->getPointerTo();
		}
		else
		{
			ret = llvm::ArrayType::get(translateType(type->refType), type->size);
		}
		
		break;
	}
	default:
		break;
	}
	if (mode == PASS_BY_REFERENCE)
		ret = ret->getPointerTo();
	return ret;
}

inline static int sizeOfDataType(Type t)
{
	int ret;
	switch (t->dtype)
	{
	case TYPE_INTEGER:
	{
		ret = 4;
		break;
	}
	case TYPE_BOOLEAN:
	{
		ret = 1;
		break;
	}
	case TYPE_CHAR:
	{
		ret = 1;
		break;
	}
	case TYPE_LIST:
	{
		ret = sizeOfDataType(t->refType) + 8;
		
		break;
	}
	case TYPE_IARRAY:
	{
		ret = sizeOfDataType(t->refType);
		break;
	}
	default:
		break;
	}
	return ret;
}

class AST
{
public:
	virtual ~AST() {}
	virtual void sem() {}

	llvm::Function *f;
	uint semantic_line_no;

	virtual void set_line(uint l_no)
	{
		this->semantic_line_no = l_no;
	}

	virtual llvm::Value *codegen()
	{
		return nullptr;
	}

	void llvm_compile_and_dump()
	{
		scopes.openScope();
		TheModule = std::make_unique<llvm::Module>("program", TheContext);
		TheFPM = std::make_unique<llvm::legacy::FunctionPassManager>(TheModule.get());

		// TheFPM->add(llvm::createPromoteMemoryToRegisterPass());
		// TheFPM->add(llvm::createMemCpyOptPass());
		// TheFPM->add(llvm::createInstructionCombiningPass());
		// TheFPM->add(llvm::createReassociatePass());
		// TheFPM->add(llvm::createGVNPass());
		// TheFPM->add(llvm::createCFGSimplificationPass());
		// // TheFPM->add(llvm::createConstantPropagationPass());
		// TheFPM->add(llvm::createDeadCodeEliminationPass());
		

		TheFPM->doInitialization();

		codegenLibs();

		this->codegen();

		bool bad = llvm::verifyModule(*TheModule, &llvm::errs());
		if (bad) 
		{
			std::cerr << std::endl << std::endl << "The IR is bad!" << std::endl;
			TheModule->print(llvm::errs(), nullptr);
			exit(1);
		}
		else
		{
			TheFPM->run(*(this->f));
			TheModule->print(llvm::outs(), nullptr);
			std::error_code EC;
			llvm::raw_fd_ostream OS("./module.imm", EC, llvm::sys::fs::F_None);
			llvm::WriteBitcodeToFile(*TheModule, OS);
			OS.flush();
		}
	}
};

class Expr : public AST
{
public:
	void type_check(Type t)
	{
		if (type == NULL)
			sem();
		if (!equalType(t, type)){
			if((t->dtype == TYPE_LIST && type->dtype == TYPE_NIL) || (t->dtype == TYPE_NIL && type->dtype == TYPE_LIST))
				return;
			error(this->semantic_line_no, "Invalid type of operand. Expected %s, found %s.", TypeToStr(t), TypeToStr(type));
		}
	}

	Type getType()
	{
		if (type == NULL)
			sem();
		return type;
	}

	virtual void checkLVal() {}

	bool checkVar() {
		return isVar;
	}

protected:
	Type type;
	bool isVar = false;
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
			s->codegen();
		return nullptr;
	}

private:
	std::vector<Stmt *> stmt_list;
};

class Var : public Expr
{
public:
	Var(const char *v, Expr *i = NULL) : var(v), index(i) {
		isVar = true;
		isArray = false;
	}

	virtual void sem() override
	{
		SymbolEntry *e = lookupEntry(var, LOOKUP_ALL_SCOPES, true, this->semantic_line_no); 
		if (e->entryType == ENTRY_FUNCTION)
			error(this->semantic_line_no, "%s is a function, expected parenthesis", e->id);
		type = e->eVariable.type;
		// TODO MAYBE FOR LIST TOO
		if (type->dtype == TYPE_IARRAY || type->dtype == TYPE_LIST)
			this->isArray = true;

		if (index != NULL){
			index->sem();
			if (index->getType()->dtype != TYPE_INTEGER)
				error(this->semantic_line_no, "Array index must be of type integer.");
			if (this->getType()->dtype != TYPE_IARRAY)
				error(this->semantic_line_no, "Expected array, found %s", TypeToStr(this->getType()));
			type = type->refType;
		}
	}

	bool isArrayIndexing()
	{
		return (index != NULL);
	}

	Expr *getIndex()
	{
		return this->index;
	}

	const char *getName()
	{
		return var;
	}

	virtual llvm::Value *codegen() override
	{
		ActivationRecord *ar = activationRecordStack.front();

		if( index == NULL )
		{
			if ( ar->isRef(var) && !isArray )
			{
				return Builder.CreateLoad(Builder.CreateLoad(ar->getAddr(var)));
			}
			else if (ar->isRef(var))
			{
				return Builder.CreateLoad(ar->getAddr(var));
			}
			else
			{
				std::cout << "DEBUGGING HERE "<< var << std::endl;
				return Builder.CreateLoad(ar->getVal(var));
			}
			return nullptr;
		}
		else 
		{
			auto *idx = this->index->codegen();
			auto array_address = Builder.CreateLoad(ar->getAddr(this->var),idx);
			auto *address_at_index = Builder.CreateGEP(array_address, idx);
			return Builder.CreateLoad(address_at_index);
    	}
    	return nullptr;
	}
	bool isArray;
private:
	const char *var;
	Expr *index;
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
			newParameter(v, type, mode, f, this->semantic_line_no);
	}

	virtual llvm::Value *codegen() override
	{
		for (auto v : var_list->getList())
		{
			activationRecordStack.front()->addArg(v, type, mode);
		}

		return nullptr;
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
		return nullptr;
	}

	std::vector<Formal *> get_formal_list()
	{
		return formal_list;
	}

	std::vector<const char *> get_arg_names()
	{
		std::vector<const char *> ret;
		for (auto f : formal_list)
		{
			for (auto name : f->get_var_list_names())
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
		SymbolEntry *f = newFunction(functionName, this->semantic_line_no);
		if (header_type == Func_Decl) /* Declarations should be forwarded */
			declareFunction(f);
		openScope();
		formal_list->passParameters(f);
		endFunctionHeader(f, type, this->semantic_line_no);
	}

	virtual Type getType()
	{
		return this->type;
	}

	virtual const char *getName()
	{
		return this->functionName;
	}

	virtual llvm::Value *codegen() override
	{
		return nullptr;
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
		return nullptr;
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
		closeScope(this->semantic_line_no);
	}

	virtual llvm::Value *codegen() override
	{
		auto newAR = new ActivationRecord();
		activationRecordStack.push_front(newAR);


		if(strcmp(this->header->getName(), "concat") == 0)
		{
			std::cout << "CODEGEN CONCAT" << std::endl;
		}
		header->getFormalList()->codegen();


		if (scopes.getFunc(header->getName()) == NULL)
		{
			llvm::FunctionType *ftype = llvm::FunctionType::get(
				translateType(this->header->getType()), activationRecordStack.front()->getArgs(), false);

			llvm::Function *func;
			if( scopes.is_initialized )
				func = llvm::Function::Create(
					ftype, llvm::Function::ExternalLinkage, header->getName(), TheModule.get());
			else
				func = llvm::Function::Create(
					ftype, llvm::Function::ExternalLinkage, "main", TheModule.get());

			activationRecordStack.front()->setFunc(func);
			scopes.addFunc(std::string(header->getName()), func);
		}
		else
			activationRecordStack.front()->setFunc(scopes.getFunc(header->getName()));

		scopes.openScope();

		llvm::Function *func = scopes.getFunc(header->getName());
		this->f = func;

		int index = 0;
		auto argNames = this->header->getFormalList()->get_arg_names();
		for (auto &Arg : func->args())
		{
			Arg.setName( argNames[index++] );
		}

		llvm::BasicBlock *FuncBB = llvm::BasicBlock::Create(TheContext, "entry", func);
		Builder.SetInsertPoint(FuncBB);
		activationRecordStack.front()->setCurrentBlock(FuncBB);

		for (auto &Arg : func->args())
		{
			auto *alloca = Builder.CreateAlloca(Arg.getType(), nullptr, Arg.getName());

			if (Arg.getType()->isPointerTy())
				activationRecordStack.front()->addAddr(Arg.getName().str(), alloca);
			else
				activationRecordStack.front()->addVal(Arg.getName().str(), alloca);
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
				// TODO return the return type of the function
				else if(func->getReturnType()->isIntegerTy(8))
					Builder.CreateRet(c8(0));
				else
					Builder.CreateRet(c1(0));
			}
		}

		activationRecordStack.pop_front();
		scopes.closeScope();


		if (activationRecordStack.size() != 0)
			Builder.SetInsertPoint(activationRecordStack.front()->getCurrentBlock());

		// if (!main)
		// 	Builder.SetInsertPoint(activationRecordStack.front()->getCurrentBlock());

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
		closeScope(this->semantic_line_no);
	}

	virtual llvm::Value *codegen()
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

		return nullptr;
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
		{
			newVariable(variable, type, this->semantic_line_no);
		}
	}

	virtual llvm::Value *codegen() override
	{
		for (const char *varName : var_list->getList())
		{
			auto llvm_type = translateType(this->type);
			auto alloca = Builder.CreateAlloca(llvm_type, nullptr, varName);
			// edw kanoume alloca ena pointer pros type char px
			// ara to alloca einai pointer pros pointer pros type char 

			activationRecordStack.front()->addVar(varName, llvm_type);
			activationRecordStack.front()->addVal(varName, alloca);
			activationRecordStack.front()->addAddr(varName, alloca);
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

	virtual void sem() override
	{
		for(Expr *expr : expr_list)
			expr->sem();
	}

	std::vector<Expr *> getList()
	{
		return expr_list;
	}

	void append(Expr *e) { expr_list.push_back(e); }

private:
	std::vector<Expr *> expr_list;
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
		error(this->semantic_line_no, "Lvalue cannot be a string literal.");
	}

	virtual llvm::Value *codegen() override
	{
		return Builder.CreateGlobalStringPtr(str);
	}

private:
	const char *str;
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

	uint semantic_line_no;

	void set_line(uint l_no)
	{
		this->semantic_line_no = l_no;
	}

	virtual void sem() override
	{
		this->expr_list->sem();
		int functionArguments = 0;
		bool argMismatch = false;
		SymbolEntry *f = lookupEntry(functionName, LOOKUP_ALL_SCOPES, true, this->semantic_line_no);
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
			if(!e->checkVar() && args->eParameter.mode == PASS_BY_REFERENCE && (paramType == typeInteger || paramType == typeBoolean || paramType == typeChar))
				error(this->semantic_line_no, "Only variables can be passed by reference.");
			args = args->eParameter.next;
		}
		if (argMismatch)
			error(this->semantic_line_no, "Expected %d arguments for function %s, but %lu were given.", functionArguments, functionName, expr_list->getList().size());
		else if (args)
		{
			while (args)
			{
				++functionArguments;
				args = args->eParameter.next;
			}
			error(this->semantic_line_no, "Expected %d arguments for function %s, but %lu were given.", functionArguments, functionName, expr_list->getList().size());
		}
	}

	virtual llvm::Value *codegen() override
	{
		llvm::Function *TheFunction = scopes.getFunc(this->functionName);

		std::vector<llvm::Value *> callArgs;

		std::vector<Expr *> functionArgs = this->expr_list->getList();

		int index = 0;
		for (auto &Arg : TheFunction->args())
		{
			if (Arg.getType()->isPointerTy())
			{
				Var *var = dynamic_cast<Var *>(functionArgs[index]);
				if (var != nullptr)
				{
					if (!var->isArrayIndexing())
					{
						if (activationRecordStack.front()->isRef(var->getName()) )
						{
							auto par = Builder.CreateLoad(activationRecordStack.front()->getAddr(var->getName()));
							callArgs.push_back(par);
						}
						else
						{
							llvm::Value *par;
							par = activationRecordStack.front()->getVal(var->getName());
							callArgs.push_back(par);
						}
					}
					else
					{
						auto idx = var->getIndex()->codegen();
						if (activationRecordStack.front()->isRef(var->getName()))
						{
							llvm::Value *par = Builder.CreateLoad(activationRecordStack.front()->getAddr(var->getName()));
							par = Builder.CreateGEP(par, idx);
							callArgs.push_back(par);
						}
						else
						{
							llvm::Value *par = activationRecordStack.front()->getVal(var->getName());
							par = Builder.CreateGEP(par, std::vector<llvm::Value *>{c32(0), idx});
							callArgs.push_back(par);
						}
					}
					index++;
					continue;
				}
				else
				{
					callArgs.push_back(functionArgs[index]->codegen());
					index++;
					continue;
				}
			}
			else
			{
				Expr *argument = functionArgs[index];
				callArgs.push_back(argument->codegen());
				index++;
			}
		}
		return Builder.CreateCall(TheFunction, callArgs);
	}

	virtual void checkLVal() override
	{
		error(this->semantic_line_no, "Lvalue cannot be a function call.");
	}

private:
	const char *functionName;
	ExprList *expr_list;
};



class ConstInt : public Expr
{
public:
	ConstInt(int n) : num(n) {}

	virtual void sem() override
	{
		type = typeInteger;
	}

	virtual llvm::Value *codegen() override
	{
		return llvm::ConstantInt::get(llvm::Type::getInt32Ty(TheContext), num);
		// return llvm::ConstantInt::get(i32, num);
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

	virtual llvm::Value *codegen() override
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
		right->sem();
		right->type_check(typeInteger);
		if (left != NULL){
			left->sem();
			left->type_check(typeInteger);
		}
		type = typeInteger;
	}

	virtual llvm::Value *codegen() override
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
		left->sem();
		right->sem();
		Type leftType = left->getType();
		Type rightType = right->getType();
		if (!equalType(leftType, rightType))
			error(this->semantic_line_no, "Operands of comparison have different types: %s and %s.", TypeToStr(leftType), TypeToStr(rightType));
		if (leftType->dtype == TYPE_INTEGER || leftType->dtype == TYPE_BOOLEAN || leftType->dtype == TYPE_CHAR)
		{
			type = typeBoolean;
			return;
		}
		else
			error(this->semantic_line_no, "Comparisons supported only for integers, booleans and characters.");
	}

	virtual llvm::Value *codegen() override
	{
		llvm::Value *l = left->codegen();
		llvm::Value *r = right->codegen();

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
			right->sem();
			right->type_check(typeBoolean);
			break;
		case AND:
		case OR:
			right->sem();
			left->sem();
			right->type_check(typeBoolean);
			left->type_check(typeBoolean);
		}
		type = typeBoolean;
	}

	virtual llvm::Value *codegen() override
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
			right->sem();
			if (right->getType()->dtype != TYPE_LIST)
				error(this->semantic_line_no, "Expected list, found %s.", TypeToStr(right->getType()));
			type = right->getType()->refType;
			break;
		case tail:
			right->sem();
			if (right->getType()->dtype != TYPE_LIST)
				error(this->semantic_line_no, "Expected list, found %s.", TypeToStr(right->getType()));
			type = right->getType();
			break;
		case nilq:
			right->sem();
			if (right->getType()->dtype != TYPE_LIST && right->getType()->dtype != TYPE_NIL)
				error(this->semantic_line_no, "Expected list, found %s.", TypeToStr(right->getType()));
			type = typeBoolean;
			break;
		case append:
			right->sem();
			left->sem();
			if (right->getType()->dtype == TYPE_NIL)
			{
				type = typeList(left->getType());
				break;
			}
			else if (!equalType(left->getType(), right->getType()->refType))
			{
				error(this->semantic_line_no, "Cannot append %s to %s.", TypeToStr(left->getType()), TypeToStr(right->getType()));
			}
			type = right->getType();
		}
	}

	virtual llvm::Value *codegen() override
	{
		llvm::Value *r;
		if(this->op != nil)
			r = this->right->codegen();
		llvm::Value *l;
		if (left != NULL)
			l = left->codegen();
		if (op == head)
		{
			// std::cout << r->getType()->getPointerElementType()->getTypeID() << std::endl;
			// auto struct_address = Builder.CreateLoad(r);
			r = Builder.CreateConstGEP1_32(r, 0);
			return Builder.CreateLoad(r);
		}
		else if (op == tail)
		{
			// r = Builder.CreateGEP(r, 1);
			r = Builder.CreateConstGEP1_32(r, 1);
			return Builder.CreateLoad(r);
		}
		else if (op == append)
		{
			auto size = 8 + sizeOfDataType(right->getType()->refType);
			auto *new_head_alloca = Builder.CreateCall(TheMalloc, {llvm::ConstantInt::get(i32, size)});

			// auto *new_head_struct = Builder.CreateLoad(new_head_alloca);

			// auto *new_val_address = Builder.CreateConstGEP1_32(new_head_struct, 1);

			auto *new_val_address = Builder.CreateConstGEP1_32(new_head_alloca, 1);
			Builder.CreateStore(l, new_val_address);

			// auto *new_head_next = Builder.CreateGEP(new_head_struct,0);
			auto *new_head_next = Builder.CreateConstGEP1_32(new_head_alloca, 0);
			Builder.CreateStore(r, new_head_next);
		}
		else if (op == nil)
		{
			auto myStructType = llvm::StructType::create(TheContext, "myStruct");
			auto myStructPtrType = llvm::PointerType::get(myStructType, 0);
			myStructType->setBody({NULL, myStructPtrType}, false);
			// ret = myStructType;
			return llvm::ConstantPointerNull::get(myStructType->getPointerTo());
		}
		else if (op == nilq)
		{
			if (llvm::ConstantPointerNull::classof(r))
				return llvm::ConstantInt::getTrue(TheContext);
			else
				return llvm::ConstantInt::getFalse(TheContext);
		}

		return nullptr;
	}

private:
	Expr *left;
	listOp op;
	Expr *right;
};


class ArrayInit : public Stmt
{
public:
	ArrayInit(Expr *name, Type t, Expr *e) : helper(name), variable(dynamic_cast<Var *>(name)), refT(t), expr(e){};
	~ArrayInit()
	{
		delete variable;
		delete type;
		delete refT;
		delete expr;
	}

	virtual void sem() override
	{
		helper->checkLVal();
		this->variable->sem();
		this->expr->sem();
		if (refT->dtype != TYPE_INTEGER && refT->dtype != TYPE_BOOLEAN && refT->dtype != TYPE_CHAR)
			error(this->semantic_line_no, "Arrays of integers, booleans and characters are only supported.");

		this->type = typeIArray(refT);
		if (expr->getType()->dtype != TYPE_INTEGER)
			error(this->semantic_line_no, "Array size must be of type integer.");
	}

	virtual llvm::Value *codegen() override
	{
		auto len = expr->codegen();
		int data_type_size = sizeOfDataType(type);
		llvm::Value *total_size = Builder.CreateMul(len, llvm::ConstantInt::get(i32, data_type_size));
		llvm::Value *alloca = Builder.CreateCall(TheMalloc, {total_size});

		alloca = Builder.CreateBitCast(alloca, translateType(type->refType)->getPointerTo() );

		// to int [] x einai pointer pros pointer pros int
		// edw kanoume gc malloc ena pointer pros int
		// kai to kanw store sto pointer pros pointer pros int

		Builder.CreateStore(alloca, activationRecordStack.front()->getAddr(variable->getName()));
		
		// activationRecordStack.front()->addVar(variable->getName(), alloca->getType());
		// activationRecordStack.front()->addVal(variable->getName(), alloca);
		// activationRecordStack.front()->addAddr(variable->getName(),alloca);

		// this->type->size = size;
		// auto *arrayType = translateType(this->type);
		// auto *alloca = Builder.CreateAlloca(arrayType, size, this->variable->getName());
		// activationRecordStack.front()->addVar(variable->getName(), this->type);
		// activationRecordStack.front()->addVal(variable->getName(), alloca);
		return nullptr;
	}

private:
	Expr *helper;
	Type type;
	Var *variable;
	Type refT;
	Expr *expr;
};

class AssignStmt : public Stmt
{
public:
	AssignStmt(Expr *l, Expr *r) : helper(l), left(dynamic_cast<Var *>(l)), right(r) {}
	~AssignStmt()
	{
		delete left;
		delete right;
	}

	virtual void sem() override
	{
		helper->checkLVal();
		left->sem();
		right->sem();
		Type ltype = left->getType();
		right->type_check(ltype);
	}

	virtual llvm::Value *codegen() override
	{
		llvm::Value *rval = right->codegen();

		ActivationRecord *ar = activationRecordStack.front();

		if (!left->isArrayIndexing())
		{
			if (ar->isRef(left->getName()) && !left->isArray)
			{
				auto *addr = Builder.CreateLoad(ar->getAddr(left->getName()));
				return Builder.CreateStore(rval, addr);
			}
			else if (ar->isRef(left->getName()))
			{
				return Builder.CreateStore(rval, ar->getAddr(left->getName()));
			}
			else
				return Builder.CreateStore(rval, ar->getVal(left->getName()));
		}
		else
		{
			llvm::Value *idx = left->getIndex()->codegen();
			auto array_address = Builder.CreateLoad(ar->getAddr(left->getName()));
			auto array_index_address = Builder.CreateGEP(array_address, idx);
			return Builder.CreateStore(rval, array_index_address);
		}
		return nullptr;
	}

private:
	Expr *helper;
	Var *left;
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
			error(this->semantic_line_no, "Exit called in non-void function.");
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
		returnExpr->sem();
		Type exprType = returnExpr->getType();
		if (!equalType(exprType, returnType)){
			if (returnType->dtype == TYPE_LIST && exprType->dtype == TYPE_NIL)
				return;
			error(this->semantic_line_no, "Invalid type of return expression: Expected %s, found %s.", TypeToStr(returnType), TypeToStr(exprType));
		}
	}

	virtual llvm::Value *codegen() override
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
	virtual llvm::Value *codegen() override
	{
		if (cond == NULL && stmt_list != NULL)
			return stmt_list->codegen();

		llvm::Value *CondV = cond->codegen();

		// Convert condition to a bool by comparing non-equal to 0.0.
		CondV = Builder.CreateICmpNE(CondV, c1(0), "if_cond");
		// CondV = Builder.CreateFCmpONE(CondV, llvm::ConstantInt::get(TheContext, llvm::APFloat(0.0)), "ifcond");

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

		if (nextIf != nullptr)
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

	virtual llvm::Value *codegen() override
	{
		initializers->codegen();

		llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
		llvm::BasicBlock *LoopBB = llvm::BasicBlock::Create(TheContext, "loop", TheFunction);
		llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(TheContext, "after");

		llvm::Value *CondV = threshold->codegen();
		if (!CondV)
			return nullptr;

		// Convert condition to a bool by comparing non-equal to 0
		CondV = Builder.CreateICmpNE(CondV, c1(0), "loopcond");

		Builder.CreateCondBr(CondV, LoopBB, AfterBB);

		// Start insertion in LoopBB.
		Builder.SetInsertPoint(LoopBB);
		activationRecordStack.front()->setCurrentBlock(LoopBB);

		loop_body->codegen();

		// Emit the step value.
		steps->codegen();

		CondV = threshold->codegen();
		if (!CondV)
			return nullptr;

		// Convert condition to a bool by comparing non-equal to 0.0.
		CondV = Builder.CreateICmpNE(CondV, c1(0), "loopcond");

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


void codegenLibs()
{
	auto *writeIntegerType = llvm::FunctionType::get(proc, std::vector<llvm::Type *>{i32}, false);
	scopes.addFunc("puti",llvm::Function::Create(writeIntegerType,llvm::Function::ExternalLinkage,"writeInteger", TheModule.get()));
	
	auto *writeBooleanType = llvm::FunctionType::get(proc, std::vector<llvm::Type *>{i1}, false);
	scopes.addFunc("putb",llvm::Function::Create(writeBooleanType,llvm::Function::ExternalLinkage,"writeBoolean", TheModule.get()));

	auto *writeCharType = llvm::FunctionType::get(proc, std::vector<llvm::Type *>{i8}, false);
	scopes.addFunc("putc",llvm::Function::Create(writeCharType,llvm::Function::ExternalLinkage,"writeChar", TheModule.get()));
	
	auto i8 = llvm::IntegerType::get(TheContext, 8);
	auto *writeStringType = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), {llvm::PointerType::get(i8, 0)}, false);
	scopes.addFunc("puts",llvm::Function::Create(writeStringType,llvm::Function::ExternalLinkage,"writeString", TheModule.get()));
	
	auto *readIntegerType = llvm::FunctionType::get(i32, std::vector<llvm::Type *>{}, false);
	scopes.addFunc("geti",llvm::Function::Create(readIntegerType,llvm::Function::ExternalLinkage,"readInteger", TheModule.get()));
	
	auto *readByteType = llvm::FunctionType::get(i8, std::vector<llvm::Type *>{}, false);
	scopes.addFunc("getb",llvm::Function::Create(readByteType,llvm::Function::ExternalLinkage,"readByte", TheModule.get()));

	auto *readCharType = llvm::FunctionType::get(i8, std::vector<llvm::Type *>{}, false);
	scopes.addFunc("getc",llvm::Function::Create(readCharType,llvm::Function::ExternalLinkage,"readChar", TheModule.get()));

	auto *readStringType = llvm::FunctionType::get(proc, std::vector<llvm::Type *>{i32, i8->getPointerTo()}, false);
	scopes.addFunc("gets",llvm::Function::Create(readStringType,llvm::Function::ExternalLinkage,"readString", TheModule.get()));

	auto absType = llvm::FunctionType::get( i32, std::vector<llvm::Type *>{i32}, false );
	scopes.addFunc("abs", llvm::Function::Create(absType,llvm::Function::ExternalLinkage,"abs", TheModule.get()));

	auto ordType = llvm::FunctionType::get( i32, std::vector<llvm::Type *>{i8}, false );
	scopes.addFunc("ord", llvm::Function::Create(ordType,llvm::Function::ExternalLinkage,"ord", TheModule.get()));

	auto chrType = llvm::FunctionType::get( i8, std::vector<llvm::Type *>{i32}, false );
	scopes.addFunc("chr", llvm::Function::Create(chrType,llvm::Function::ExternalLinkage,"chr", TheModule.get()));

	auto *strlenType = llvm::FunctionType::get(i32, std::vector<llvm::Type *>{i8->getPointerTo()}, false);
	scopes.addFunc("strlen", llvm::Function::Create(strlenType, llvm::Function::ExternalLinkage,"strlen", TheModule.get()));

	auto *strcmpType = llvm::FunctionType::get(i32, std::vector<llvm::Type *>{i8->getPointerTo(), i8->getPointerTo()}, false);
	scopes.addFunc("strcmp", llvm::Function::Create(strcmpType, llvm::Function::ExternalLinkage,"strcmp", TheModule.get()));

	auto *strcpyType = llvm::FunctionType::get(proc, std::vector<llvm::Type *>{i8->getPointerTo(), i8->getPointerTo()}, false);
	scopes.addFunc("strcpy", llvm::Function::Create(strcpyType, llvm::Function::ExternalLinkage,"strcpy", TheModule.get()));

	auto *strcatType = llvm::FunctionType::get(proc, std::vector<llvm::Type *>{i8->getPointerTo(), i8->getPointerTo()},false);
	scopes.addFunc("strcat", llvm::Function::Create(strcatType, llvm::Function::ExternalLinkage, "strcat", TheModule.get()));
	scopes.is_initialized = false;

	// auto i64 = llvm::IntegerType::get(TheContext, 64);

	llvm::FunctionType *malloc_type = llvm::FunctionType::get(llvm::PointerType::get(i32, 0), {i32}, false);
    TheMalloc = llvm::Function::Create(malloc_type, llvm::Function::ExternalLinkage, "GC_malloc", TheModule.get());
    llvm::FunctionType *init_type = llvm::FunctionType::get(llvm::Type::getVoidTy(TheContext), {}, false);
    TheInit = llvm::Function::Create(init_type, llvm::Function::ExternalLinkage, "GC_init", TheModule.get());
}