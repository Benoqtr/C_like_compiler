#pragma once
#include "config/config.h"
#include <iostream>
#include <memory>
#include <utility>

namespace compile{

    //regular Expression and regular Grammar
    using compileConfig = config::Config;

    //token pairs
    using tokensPtr = std::shared_ptr<std::vector<
    std::pair<std::string,std::string>>>;

    //ProgramAST pointer
    using ASTRoot = std::shared_ptr<ProgramAST>;

    //IR ostream
    using IRstream = std::ostream;


    class Compile{
    public:
        compileConfig config;

        std::string sourceFilePath;
        std::string destinationFilePath;

        tokensPtr tokens;
        ASTRoot ASTree;
        IRstream llvmIR;

        Compile(compileConfig config, const std::string& sourceFilePath,
        const std::string& destinationFilePath);

        Compile(compileConfig config);

        void initToken();
        void initAST();
        void initIR();
        void compile();
    };
}