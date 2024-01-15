#pragma once
#include <memory>

namespace grammar{

using globalConfig = config::Config;
using LL1grammarInfo = LL1::LL1grammarInfo;

class ASTConstuctor{
public:
    ASTConstuctor(globalConfig config, tokensPtr tokens);
    std::shared_ptr<ProgramAST> getASTree();
private:
    globalConfig config;
    tokensPtr tokens;
    std::shared_ptr<ProgramAST> ASTree;
    void ll1construct();
};

}

