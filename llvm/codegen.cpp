#include "codegen.hpp"
#include <memory>

#include <llvm/IR/Instructions.h>
#include <llvm/IR/BasicBlock.h>

#include "symbol.hpp"
#include "error.hpp"
#include "ast.hpp"

/*******************************************************************************
 * ActivationRecord
 *******************************************************************************/

ActivationRecord::ActivationRecord() {
    this->func      = nullptr;
    this->currentBB = nullptr;
    this->hasRet    = false;
}

ActivationRecord::~ActivationRecord() {
}

void ActivationRecord::setFunc(llvm::Function *func) {
    this->func = func;
}

void ActivationRecord::setCurrentBlock(llvm::BasicBlock *BB) {
    this->currentBB = BB;
    this->hasRet    = false;
}

void ActivationRecord::addArg(std::string name, Type type, PassMode mode) {
    auto *t = translateType(type, mode);
    args.push_back(t);
    varTypes[name] = t;
}

void ActivationRecord::addVar(std::string name, Type type, PassMode mode) {
    varTypes[name] = translateType(type, mode);
}

void ActivationRecord::addVar(std::string name, llvm::Type *type) {
    varTypes[name] = type;
}

void ActivationRecord::addVal(std::string name, llvm::Value *val) {
    this->varValues[name] = val;
}

void ActivationRecord::addAddr(std::string name, llvm::Value *addr) {
    this->addresses[name] = addr;
}

void ActivationRecord::addRet() {
    this->hasRet = true;
}

const std::vector<llvm::Type*>& ActivationRecord::getArgs() const {
    return this->args;
}

const std::vector<std::string>& ActivationRecord::getArgNames() const {
    return this->argNames;
}

llvm::Type* ActivationRecord::getVar(std::string name) {
    return this->varTypes[name];
}

llvm::Value* ActivationRecord::getVal(std::string name) {
    return this->varValues[name];
}

llvm::Value* ActivationRecord::getAddr(std::string name) {
    return this->addresses[name];
}

bool ActivationRecord::isRef(std::string name) 
{   
    return this->varTypes[name]->isPointerTy();
}

bool ActivationRecord::hasReturn() {
    return this->hasRet;
}

bool ActivationRecord::varExists(std::string name)
{
    return (this->varTypes.find(name) != this->varTypes.end());
}

llvm::Function* ActivationRecord::getFunc() {
    return this->func;
}

llvm::BasicBlock* ActivationRecord::getCurrentBlock() {
    return this->currentBB;
}

/*******************************************************************************
 * Scope
 *******************************************************************************/

LLVMScope::LLVMScope() {}

LLVMScope::~LLVMScope() {}

void LLVMScope::openScope() {
    this->functions.push_front( std::unordered_map<std::string, llvm::Function*>() );
}

bool LLVMScope::empty()
{
    return this->functions.empty();
}

void LLVMScope::closeScope() {
    if (this->functions.empty()) {
        warning("No scopes to close");
        return;
    }
    this->functions.pop_front();
}

void LLVMScope::addFunc(std::string id, llvm::Function *func) {
    this->is_initialized = true;
    this->functions.front()[id] = func;
}

llvm::Function* LLVMScope::getFunc(std::string id) {
    for ( auto funcs : this->functions ) 
    {
        if (funcs.find(id) != funcs.end())
            return funcs[id];
    }
    return NULL;
}