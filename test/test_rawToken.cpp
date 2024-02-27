#include "tokenizer.h"
#include "config.h"
#include <iostream>

using config::Config;
using lexical::Tokenizer;
using lexical::rawTokenPtr;

#define rePath R"(regular.br)"
#define gmPath R"(grammar.bg)"
#define fPath R"(func.b)"

int main(){
    Config config(rePath,gmPath);
    
    Tokenizer tokenizer(config,fPath);

    rawTokenPtr raw_tokens = tokenizer.getRawToken();

    while (!(*raw_tokens).empty()) {
        std::string token = (*raw_tokens).front();
        std::cout << token << std::endl;

        (*raw_tokens).pop();  // 弹出队列头部元素
    }
}