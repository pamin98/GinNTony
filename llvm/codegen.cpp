/*******************************************************************************
 *                                                                             *
 *  Filename    : codegen.cpp                                                  *
 *  Project     : Alan Compiler                                                *
 *  Version     : 1.0                                                          *
 *  Author      : Spiros Dontas                                                *
 *  Email       : spirosdontas@gmail.com                                       *
 *                                                                             *
 *  Description : Codegen source file (llvm stuff)                             *
 *                                                                             *
 *******************************************************************************/

#include "codegen.hpp"
// #include <message/message.hpp>
#include <memory>

#include <llvm/IR/Instructions.h>
#include <llvm/IR/BasicBlock.h>

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

void ActivationRecord::addArg(std::string name, sem::TypePtr type, sem::PassMode mode) {
    auto *t = translateType(type, mode);
    args.push_back(t);
    varTypes[name] = t;
}

void ActivationRecord::addVar(std::string name, sem::TypePtr type, sem::PassMode mode) {
    varTypes[name] = translateType(type, mode);
}

void ActivationRecord::addVal(std::string name, llvm::AllocaInst *val) {
    this->varValues[name] = val;
}

void ActivationRecord::addAddr(std::string name, llvm::AllocaInst *addr) {
    this->addresses[name] = addr;
}

void ActivationRecord::addRet() {
    this->hasRet = true;
}

const TypeVec& ActivationRecord::getArgs() const {
    return this->args;
}

llvm::Type* ActivationRecord::getVar(std::string name) {
    return this->varTypes[name];
}

llvm::AllocaInst* ActivationRecord::getVal(std::string name) {
    return this->varValues[name];
}

llvm::AllocaInst* ActivationRecord::getAddr(std::string name) {
    return this->addresses[name];
}

bool ActivationRecord::isRef(std::string name) {
    return this->varTypes[name]->isPointerTy();
}

bool ActivationRecord::hasReturn() {
    return this->hasRet;
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

Scope::Scope() {  }

Scope::~Scope() {  }

void Scope::openScope() {
    this->functions.push_front(FuncMap());
}

void Scope::closeScope() {
    if (this->functions.empty()) {
        warning("No scopes to close");
        return;
    }
    this->functions.pop_front();
}

void Scope::addFunc(std::string id, llvm::Function *func) {
    this->functions.front()[id] = func;
}

llvm::Function* Scope::getFunc(std::string id) {
    for (auto funcs : this->functions) {
        if (funcs.find(id) != funcs.end())
            return funcs[id];
    }
}