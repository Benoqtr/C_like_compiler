#pragma once
#include <memory>

namespace grammar{

using compileConfig = compile::Config;
using ASTRoot = compile::ASTRoot;
using tokensPtr = compile::tokensPtr

using LL1grammarInfo = LL1::LL1grammarInfo;

class ASTConstuctor{
public:
    ASTConstuctor(compileConfig config, tokensPtr tokens);
    ASTRoot getASTree();
private:
    compileConfig config;
    tokensPtr tokens;
    ASTRoot ASTree;
    void ll1construct();
};

}

