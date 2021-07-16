#include "ast.hpp"


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