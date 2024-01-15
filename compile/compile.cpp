#pragma once
#include "compile/compile.h"

using namespace compile;

void Compile::initToken(){
    lexical::Tokenizer tokenier(config, sourceFilePath);
    tokens = tokenizer.getTokens();
}

void Compile::initAST(){
    grammar::ASTconstructor ASTor(config, tokens);
    ASTree = ASTor.getASTree();
}

void Compile::initIR(){
    codegen::IRconstructor IRor(ASTree);
    llvmIR = IRor.getLlvmIR();
}

void Compile::initOBJ(){
    obj::OBJconstructor OBJor(llvmIR,destinationFilePath);
    OBJor.generateFile();
}

void Compile::compile(){
    void initToken();
    void initAST();
    void initIR();
    void initObj();
}

