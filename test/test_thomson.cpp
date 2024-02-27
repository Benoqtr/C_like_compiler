#include "regularEngine.h"
#include "config.h"
#include <iostream>

using config::Config;

#define rePath R"(regular.br)"
#define gmPath R"(grammar.bg)"

int main(){
    Config config(rePath,gmPath);
    
    for (const auto& pair : *(config.regularExpressions)) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    std::cout << std::endl;

    for (const auto& mapEntry : *(config.regularGrammars)) {
        std::cout << mapEntry.first << ":" << std::endl;

        for (const auto& vectorEntry : mapEntry.second) {
            std::cout << "  [";

            for (const auto& str : vectorEntry) {
                std::cout << " " << str << " ";
            }
            std::cout << " ]" << std::endl;
        }
    }
}