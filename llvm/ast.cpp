#include "ast.hpp"

LLVMContext AST::TheContext;
IRBuilder<> AST::Builder(TheContext);
std::unique_ptr<Module> AST::TheModule;

static llvm::Type *i32 = llvm::Type::getInt32Ty(TheContext);
static llvm::Type *i8 = llvm::Type::getInt8Ty(TheContext);
static llvm::Type *proc = llvm::Type::getVoidTy(TheContext);