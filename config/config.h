#pragma once
#include <vector>
#include <map>
#include <memory>

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

    Config(const std::string& rePath,const std::string& gmPath);
private:
    bool Initres(const std::string& rePath);
    bool Initgms(const std::string& gmPath);
};

}