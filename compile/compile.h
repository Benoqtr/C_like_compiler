#pragma once
#include "config/config.h"
#include <iostream>
#include <memory>
#include <utility>

namespace compile{

    class Compile{
    public:
        config::Config config;

        std::string& sourceFilePath;
        std::string& destinationFilePath;

        std::shared_ptr<std::vector<
        std::pair<std::string,std::string>>> tokens;

        std::shared_ptr<ProgramAST> ASTree;

        std::ostream& llvmIR;

        Compile(config::Config config, std::string& sourceFilePath,
        std::string& destinationFilePath):
        config(config),sourceFilePath(sourceFilePath),
        destinationFilePath(destinationFilePath){}
        void initToken();
        void initAST();
        void initIR();
        void compile();
    };
}