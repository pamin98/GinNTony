/*******************************************************************************
 *                                                                             *
 *  Filename    : codegen.hpp                                                  *
 *  Project     : Alan Compiler                                                *
 *  Version     : 1.0                                                          *
 *  Author      : Spiros Dontas                                                *
 *  Email       : spirosdontas@gmail.com                                       *
 *                                                                             *
 *  Description : Codegen header file (llvm stuff)                             *
 *                                                                             *
 *******************************************************************************/

#ifndef __CODEGEN_HPP__
#define __CODEGEN_HPP__

#include <memory>
#include <deque>
#include <unordered_map>

#include <llvm/IR/Instructions.h>
#include <llvm/IR/BasicBlock.h>

#include <symbol/types.hpp>
#include <symbol/entry.hpp>

/*******************************************************************************
 * FuncStack :
 *   - used for checking variables and basicblocks.
 *   > When we find a function declaration we need to remember the previous
 *   > BasicBlock of the previous function so that we can continue to emit code
 *   > there after finishing up here
 * FuncMap :
 *   - used to fetch Function* for the "active" functions.
 *   > This will help us check which arguments need to be passed by reference
 *   > so that we know a var is needed to be passed there.
 *******************************************************************************/

/*******************************************************************************
 ****************************** Class Definitions ******************************
 *******************************************************************************/

class ActivationRecord;

/*******************************************************************************
 * ActivationRecord Class
 *   - args :
 *     > Used to hold argument types so that we can pass them to
 *     > `llvm::FunctionType::get( llvm::Type*,
 *                                 args,
 *                                 false )`
 *   - varTypes :
 *     > Used to hold the types of all scope variables.
 *     > Useful to know when we have referenced variables
 *     > ( as parameters that is ).
 *   - varValues :
 *     > Used to hold values of AllocaInst.
 *   - addresses :
 *     > Used to hold addresses of referenced values.
 *   - currentBB :
 *     > The currentBasicBlock for this function.
 *******************************************************************************/
class ActivationRecord {
    private :
        llvm::Function   *func;
        std::vector<llvm::Type*>                            args;
        std::unordered_map<std::string, llvm::Type*>        varTypes;
        std::unordered_map<std::string, llvm::AllocaInst*>  varValues;
        std::unordered_map<std::string, llvm::AllocaInst*>  addresses;
        llvm::BasicBlock                                    *currentBB;
        bool                                                hasRet;
    public :
        ActivationRecord();
        ~ActivationRecord();

        void setFunc(llvm::Function *func);
        void setCurrentBlock(llvm::BasicBlock *BB);

        void addArg(std::string name, sem::TypePtr type, sem::PassMode mode);
        void addVar(std::string name, sem::TypePtr type, sem::PassMode mode = sem::PassMode::VALUE);
        void addVal(std::string name, llvm::AllocaInst *val);
        void addAddr(std::string name, llvm::AllocaInst *addr);
        void addRet();

        const TypeVec& getArgs() const;
        llvm::Type* getVar(std::string name);
        llvm::AllocaInst* getVal(std::string name);
        llvm::AllocaInst* getAddr(std::string name);
        bool isRef(std::string name);
        bool hasReturn();

        llvm::Function* getFunc();
        llvm::BasicBlock* getCurrentBlock();
};

class LLVMScope {
    private:
        std::deque<FuncMap> functions;
    public:
        Scope();
        ~Scope();

        void openScope();
        void closeScope();
        void addFunc(std::string id, llvm::Function *func);
        llvm::Function* getFunc(std::string id);
};


#endif