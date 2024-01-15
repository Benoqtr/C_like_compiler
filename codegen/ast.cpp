#pragma once
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/Twine.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>

using namespace llvm;

ProgramAST::InitializeModule() {//Excute at the begining of IR generating.
  // Open a new context and module.
  TheContext = std::make_unique<LLVMContext>();
  TheModule = std::make_unique<Module>("TheModule", *TheContext);

  // Create a new builder for the module.
  Builder = std::make_unique<IRBuilder<>>(*TheContext);
}

ProgramAST::codegen(){//Toppest codegen
    std::unique_ptr<DeclAST> decl;
    while(!declList.empty()){
        decl = declList.pop();
        if(decl.codegen() == nullptr)
            std::cerr << "At ProgramAST\n" << decl.ErrorInfoBack <<std::endl;
    }
}

GloVarDeclAst::codegen(){
    Twine _name(name); 
    auto globalVar = std::make_unique<GlobalVariable>(
        TheModule,//module
        llvm::Type::getInt32Ty(context),//32bit int type
        false,//constant
        llvm::GlobalValue::ExternalLinkage,//link type
        nullptr,//init value
        _name//variable name
        isExternallyInitialized = true
    );
    return globalVar;
}

class FunctionAst : public DeclAST {
    std::string retType;
    std::string name;
    std::queue<map<std::string,std::string>> ParameterList;
    std::queue<StatAST> statList;
public:
    FunctionAst(std::string retType,
    std::string name,
    std::queue<map<std::string,std::string>> ParameterList,
    std::queue<StatAST> statList)
    : retType(retType), name(name),
    ParameterList(ParameterList), statList(statList){}
    Value *codegen() override;
};

FunctionAST::codegen{
    llvm::FunctionType* ReturnType = llvm::FunctionType::get(builder.getInt32Ty(), false);
    while(!ParameterList.empty){
        
    }
    llvm::Type* paramTypes[] = {intType, doubleType};
    llvm::ArrayRef<llvm::Type*> params(paramTypes);
    llvm::Function* mainFunction = llvm::Function::Create(mainFunctionType, llvm::Function::ExternalLinkage, "main", &module);
    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(context, "entry", mainFunction);
    builder.SetInsertPoint(entryBlock);

    llvm::Value* loadedGlobalVar = builder.CreateLoad(globalVar);
    builder.CreateRet(loadedGlobalVar);
}

GloVarDeclAst::codegen(){
    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(context, "entry", mainFunction);
}


int id ;