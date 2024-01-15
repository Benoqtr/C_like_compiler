#include "config/config.cpp"
#include "grammar/grammar.cpp"

int main(){
    config::Config config("../config/regular.br","../config/grammar.bg");
    grammar::LL1Parser ll1Parser(config);
    ll1Parser.calculateFirstSet(ll1Parser.config.regularGrammars);
    // 遍历输出 firstSetsMap
    std::cout << "Contents of firstSetsMap:" << std::endl;
    for (const auto& pair : ll1Parser.firstSetsMap) {
        std::cout << pair.first  << ": {";

        // 遍历输出每个 set 中的元素
        for (const std::string& element : pair.second) {
            std::cout << element << ",";
        }

        std::cout << "}" << std::endl;
    }
}