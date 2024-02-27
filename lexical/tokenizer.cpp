#pragma once
#include "tokenizer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <string>

namespace lexical{


// Constructor takes the input file name
Tokenizer::Tokenizer(const Config& config,
const std::string& filePath) 
: config(config),sourceFilePath(filePath){
    std::ifstream inputFile(filePath);
    if (inputFile.is_open()) {
        // Read the content of the file into the program string
        program << inputFile.rdbuf();
        inputFile.close();
    } else {
        std::cerr << "Error opening file: " << filePath << std::endl;
        std::exit(EXIT_FAILURE);
    }
}


// Tokenize the program and store tokens in a queue
bool Tokenizer::splitToken() {
    raw_tokens = std::make_shared<std::queue<std::string>>();
    std::string token;
    
    // Tokenize using space or newline as delimiters
    while (program >> token) {
        (*raw_tokens).push(token);
    }

    gotRawToken = true;
    return true;
}

rawTokenPtr Tokenizer::getRawToken(){
    if(gotRawToken) return raw_tokens;
    splitToken();
    return raw_tokens;
}

// // Get the next token from the queue
// void Tokenizer::match() {
//     regularEngine engine(config.regularExpressions);
//     while(!raw_tokens.empty()) {
//         std::string raw_token = raw_tokens.front();
//         raw_tokens.pop();
//         tokenType = engine.match(raw_token)
//         auto token = std::pair<std::string, std::string>(tokenType,raw_token);
//         tokens.push_back(token);
//     }
// }

// tokensPtr Tokenizer::getTokens(){
//     tokenize();
//     match();
//     tokensPtr tokenptr = std::make_shared<
//     std::vector<std::pair<std::string, std::string>> tokens;
//     return tokenptr;
// }

}//namespace lexical