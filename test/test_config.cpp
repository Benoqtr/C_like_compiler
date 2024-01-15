#include "config/config.cpp"

int main(){
    Config config("../config/regular.br","../config/grammar.bg");
    
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