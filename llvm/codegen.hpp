
#ifndef __CODEGEN_HPP__
#define __CODEGEN_HPP__

#include <memory>
#include <deque>
#include <unordered_map>

#include <llvm/IR/Instructions.h>
#include <llvm/IR/BasicBlock.h>

// #include "types.hpp"
// #include "entry.hpp"

#include "symbol.hpp"

class ActivationRecord;

class ActivationRecord 
{
    private :
        llvm::Function   *func;
        std::vector<llvm::Type*>                            args;
        std::vector<std::string>                            argNames;
        std::unordered_map<std::string, llvm::Type*>        varTypes;
        std::unordered_map<std::string, llvm::Value*>       varValues;
        std::unordered_map<std::string, llvm::Value*>       addresses;
        llvm::BasicBlock                                    *currentBB;
        bool                                                hasRet;
        // deikti pros frame pointer
    public :
        ActivationRecord();
        ~ActivationRecord();

        void setFunc(llvm::Function *func);
        void setCurrentBlock(llvm::BasicBlock *BB);

        void addArg(std::string name, Type type, PassMode mode);
        void addVar(std::string name, Type type, PassMode mode = PASS_BY_VALUE);
        void addVal(std::string name, llvm::Value *val);
        void addAddr(std::string name, llvm::Value *addr);
        void addRet();
        bool varExists(std::string name);

        const std::vector<llvm::Type*>& getArgs() const;
        const std::vector<std::string>& getArgNames() const;
        llvm::Type* getVar(std::string name);
        llvm::Value* getVal(std::string name);
        llvm::Value* getAddr(std::string name);
        bool isRef(std::string name);
        bool hasReturn();

        llvm::Function* getFunc();
        llvm::BasicBlock* getCurrentBlock();
};

class LLVMScope {
    private:
        std::deque<std::unordered_map<std::string, llvm::Function*>> functions;
        
    public:
        LLVMScope();
        ~LLVMScope();

        bool is_initialized = false;

        void openScope();
        void closeScope();
        bool empty();
        void addFunc(std::string id, llvm::Function *func);
        llvm::Function* getFunc(std::string id);
};


#endif