#pragma once
#include "grammar/LL1.h"
#include <algorithm>
#include <set>

namespace LL1{

LL1grammarInfo::LL1grammarInfo(productionMapPtr productionMap)
:productionMap(productionMap){
    initNon_terminalSet();
    initTerminalSet();
}

LL1grammarInfo::initNon_terminalSet(){
    for (const auto& mapEntry : *(productionMap)) 
        non_terminals.insert(mapEntry.first);    
}

LL1grammarInfo::initTerminalSet(){
    if(non_terminals.empty())
        initNon_terminalSet()
    for (const auto& mapEntry : *(productionMap)) {
        for (const auto& vectorEntry : mapEntry.second) {
            for (const auto& str : vectorEntry) {//terminal symbol
                if (non_terminals.find(str) == non_terminals.end()){
                    terminals.insert(str);
                }
            }
        }
    }
}

LL1Constructor::LL1Constructor(
    std::shared_ptr<LL1grammarInfo> grammarInfo, tokensPtr tokens)
    :grammarInfo(grammarInfo),tokens(tokens){}

std::shared_ptr<ProgramAST> LL1Constructor::getASTree(){
    if(!ASTree == nullptr){
        return ASTree;
    }
    genTree();
    if(ASTree == nullptr){
        std::cerr << "Failed to genTree." << std::endl;
        return nullptr
    }
    return ASTree;
}

void LL1Constructor::genTable(std::shared_ptr<LL1grammarInfo> 
grammarInfo){
    LL1TableConstructor(grammarInfo);
    LL1Table = LL1TableConstructor.getTable();
}

void LL1Constructor::parse(grammarInfo,tokens,LL1Table){

}

void LL1Constructor::genTree(stack){

}

void LL1TableConstructor::calculateFirstSet(){
    initNonterminalSet();
    initTerminalSet();
    bool firstSetChanged = true;
    while(firstSetChanged){
        firstSetChanged = false;
        for (const auto& productions : *(productionMap)) {
            //productions.first -> [list1,list2,...]
            for (const auto& production : productions.second) {
                bool episionAll = true;
                for(const auto& element : production){
                    //let setA contains all element seti contains
                    if(haveAddNewSymbol(firstSetsMap[productions.first],firstSetsMap[element])){
                        firstSetChanged = true;
                    }
                    //if find ε, it is necessary to add next symbol's First set
                    if(firstSetsMap[element].find("ε") != firstSetsMap[element].end()){
                        episionAll = false;
                        break;
                    }
                }
                if(episionAll)
                    firstSetsMap[productions.first].insert("ε");
            }
        }
    }
}

void LL1TableConstructor::calculateFollowSet() {
    followSetsMap[startSymbol].insert("$");

    bool followSetChanged = true;
    while (followSetChanged) {
        followSetChanged = false;
        for (const auto& productions : *productionMap) {
            for (const auto& production : productions.second) {
                for (const auto& element : production){
                    const std::string& symbol = production[i];

                    if (non_terminals.find(symbol) != non_terminals.end()) {
                        // Non-terminal symbol
                        // Update follow set using next symbols in the production
                        for (std::size_t j = i + 1; j < production.size(); ++j) {
                            if (haveAddNewSymbol(followSetsMap[symbol], firstSetsMap[production[j]])) {
                                followSetChanged = true;
                            }

                            if (firstSetsMap[production[j]].find("ε") == firstSetsMap[production[j]].end()) {
                                // ε not in first set, stop updating follow set
                                break;
                            }
                        }

                        // If the last symbols in the production can derive ε, update follow set
                        if (i == production.size() - 1 || haveAddNewSymbol(followSetsMap[symbol], followSetsMap[productions.first])) {
                            followSetChanged = true;
                        }
                    }
                }
            }
        }
    }

    // Now followSetsMap contains the final follow sets
    // You may want to assign followSetsMap to your member variable
    followSetsMap.swap(followSetsMap);
}


// add a set to another,and ε will not be added 
bool LL1TableConstructor::tryAddNewSymbol(std::set<std::string>& dstSet,std::set<std::string>& srcSet){
    //differenceSet{} = srcSet{} - dstSet{}
    std::set<std::string> differenceSet;
    std::set_difference(srcSet.begin(), srcSet.end(), dstSet.begin(), dstSet.end(),
                        std::inserter(differenceSet, differenceSet.begin()));

    differenceSet.erase("ε");
    if (!differenceSet.empty()) {//add new
        dstSet.insert(differenceSet.begin(), differenceSet.end());
        return true;
    } else {
        return false;
    }
}

bool LL1Parser::parse(){
    while (!parsingStack.empty() && 
    parsingTokenIndex < (*tokens).size()) {

        std::string stackTop = parseStack.top();
        auto curToken = (*tokens)[parsingTokenIndex];

        //terminal
        if(terminals.find(stackTop)! = terminals.end()){
            //match
            if(curToken.second == stackTop){
                parseStack.pop();
                node = buildASTnode(stackTop);//ing
                resultStack.push(node);
                reductionResultStack();//ing
            }
            else{//error detaction
                std::cerr << "terminal Failed at token num " <<
                << parsingTokenIndex <<" : ["<<
                curToken.first<<", "<<curToken.second<<
                " ]"<<std::endl;
                break;
            }
            parsingTokenIndex++;
        //non_terminal
        } else if(non_terminals.find(stackTop) != non_terminals.end()){
            ll1TableEntry entryMap = (*LL1Table)[stackTop];
            //match
            if(entryMap.find(curToken.second) != entryMap.end()){
                parseStack.pop();
                for(const auto& symbol : entryMap[curToken.second]){
                    parseStack.push(symbol);
                }
                std::pair<std::string,std::string> 
                non_terminal_token(stackTop, "");//ing
                resultStack.push(non_terminal_token);
            }
            else{//error detaction
                std::cerr << "non_terminal Failed at token num " <<
                << parsingTokenIndex <<" : ["<<
                curToken.first<<", "<<curToken.second<<
                " ] : "<<stackTop<<std::endl;
                break;
            }
        } else {
            std::cerr << "strang error: no matched grammar symbol"
            << std::endl;
            break;
        }
    }
}

}