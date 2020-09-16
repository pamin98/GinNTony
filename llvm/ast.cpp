#include "ast.hpp"

LLVMContext AST::TheContext;
IRBuilder<> AST::Builder(TheContext);
std::unique_ptr<Module> AST::TheModule;

Type *AST::i8;
Type *AST::i32;
Type *AST::i64;