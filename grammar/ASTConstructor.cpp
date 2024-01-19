#include "grammar/ASTConstructor.h"

namespace grammar{

ASTConstuctor::ASTConstuctor(compileConfig config, tokensPtr tokens)
:config(config),tokens(tokens){}

void ASTConstuctor::getASTree(){
    ll1construct();
    return ASTree;
}

void ASTConstuctor::ll1construct(){
    auto grammarInfo = std::make_shared<LL1grammarInfo>(config.regularGrammars);
    LL1constructor constructor(grammarInfo, tokens);
    ASTree = constructor.getASTree();
}

}//namespace grammar