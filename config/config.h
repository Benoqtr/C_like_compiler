#pragma once
#include <vector>
#include <map>
#include <memory>
#include <string>

namespace config{

//map non_terminal symbol to all its production lists 
using productionMapPtr = std::shared_ptr<
    std::map<std::string,
        std::vector<std::vector<std::string>>>>;

//map type to its regular Expression
using reExpressionsMapPtr = std::shared_ptr<std::map<std::string,std::string>>;

            
class Config{
public:
    //regular expressions
    reExpressionsMapPtr regularExpressions;
    //regular grammars
    productionMapPtr regularGrammars;

    Config(const std::string& regularPath,const std::string& grammarPath);
private:
    bool Initres(const std::string& regularPath);
    bool Initgms(const std::string& grammarPath);
};

}