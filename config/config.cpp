#pragma once
#include "config.h"
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace config;

Config::Config(const std::string& rePath,const std::string& gmPath){
    if(!Initres(rePath)){
        std::cerr << "Failed to Initres." << std::endl;
    }
    if(!Initgms(gmPath)){
        std::cerr << "Failed to Initgms." << std::endl;
    }
}

bool Config::Initres(const std::string& rePath){
    std::ifstream file(rePath);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl 
        << rePath << std::endl;
        return false;
    }

    regularExpressions = std::make_shared<std::map<std::string, std::string>>();

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {//remove empty line
            continue;
        }

        std::istringstream iss(line);
        std::string type, expression;

        if (iss >> std::ws >> type >> std::ws >> expression) {//remove empty words
            (*regularExpressions)[type] = expression;
        }
    }

    return true;
}

bool Config::Initgms(const std::string& gmPath){
    std::ifstream file(gmPath);

    if (!file.is_open()) {
        std::cerr << "Failed to open the file." << std::endl 
        << gmPath << std::endl;
        return false;
    }

    regularGrammars = std::make_shared<std::map<std::string,
        std::vector<std::vector<std::string>>>>();

    std::string line;
    while (std::getline(file, line)) {//handle the text
        if (line.empty()) {//remove empty line
            continue;
        }

        std::istringstream iss(line);
        std::string non_terminal;
        std::vector<std::vector<std::string>> cardss;//expressions connected by '|' op
        std::vector<std::string> cards;//expression

        iss >> std::ws >> non_terminal;

        std::string word;
        iss >> std::ws >> word;
        if (word != "->") {//remove "->"
            std::cerr << "Grammar Expression Error while at Nonterminal: " 
            << non_terminal <<std::endl;
            return false;
        } else {
            while(iss >> std::ws >> word){//handle the line
                if(word != "|"){//handle the '|' op
                    cards.push_back(word);
                }
                else{
                    cardss.push_back(cards);
                    cards.clear();
                }
            }
            cardss.push_back(cards);
            cards.clear();
        }
        //read a line
        (*regularGrammars)[non_terminal] = cardss;
    }

    return true;
}
