#pragma once
#include "grammar/LL1.h"
#include <algorithm>
#include <set>

namespace LL1{

LL1grammarInfo::LL1grammarInfo(productionMapPtr productionMap)
:productionMap(productionMap){
    initNon_terminalSet();
    initTerminalSet();
    initStartSymbol()
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

LL1grammarInfo::initStartSymbol(){
    startSymbol = *(productionMap)[0].first;
}

LL1Constructor::LL1Constructor(
    const LL1grammarInfo& grammarInfo, tokensPtr tokens)
    :grammarInfo(grammarInfo),tokens(tokens){}

ASTRoot LL1Constructor::getASTree(){
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

void LL1Constructor::genTable(const LL1grammarInfo& grammarInfo){
    LL1TableConstructor(grammarInfo);
    LL1Table = LL1TableConstructor.getTable();
}

void LL1Constructor::parse(grammarInfo,tokens,LL1Table){
    LL1Parser(grammarInfo,tokens,LL1Table);
    ASTree = LL1Parser.getTree();
}

void LL1TableConstructor::isTerminal(const std::string& symbol){
    if (grammarInfo.terminals.find(symbol) != grammarInfo.terminals.end()){
        return true;
    }
    return false;
}

void LL1TableConstructor::haveEpision(const std::set<std::string>& set){
    if (set.find("ε") != set.end()){
        return true;
    }
    return false;
}

void LL1TableConstructor::calculateFirstSet(){
    //terminal add itself
    for(const auto& terminal: grammarInfo.terminals)
        firstSetsMap[terminal].insert(terminal);
    //non_terminal circulation
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
                    if(!haveEpision(firstSetsMap[element])){
                        episionAll = false;
                        break;//stop to add
                    }
                }
                if(episionAll){
                    firstSetsMap[productions.first].insert("ε");
                    firstSetChanged = true;
                }
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
            //productions.first is A, which A→X1X2…Xn
            for (const auto& production : productions.second) {
                //production[i] is xi
                for (std::size_t i = 0; i< production.size(); ++i){
                    const std::string& symbol = production[i];

                    if (!isTerminal(symbol)) {
                        bool episionAll = true;
                        // Non-terminal symbol
                        // Update follow set using next symbols in the production
                        for (std::size_t j = i + 1; j < production.size(); ++j) {
                            if (tryAddNewSymbol(followSetsMap[symbol], firstSetsMap[production[j]])) {
                                followSetChanged = true;
                            }
                            if (!haveEpision(firstSetsMap[production[j]])) {
                                // ε not in first set, stop updating follow set
                                episionAll = false;
                                break;
                            }
                        }
                        // If the last symbols in the production can derive ε, update follow set
                        if (episionAll) {
                            tryAddNewSymbol(followSetsMap[symbol], firstSetsMap[productions.first]);
                            followSetChanged = true;
                        }
                    }
                }
            }
        }
    }
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

void LL1TableConstructor::constructLL1Table(){
    LL1Table = std::make_shared<LL1Table>();

    // 步骤4：填充LL(1)分析表
    for (const auto& nonTerminal : grammarInfo.getNonTerminals()) {
        for (const auto& production : grammarInfo.getProductionsForNonTerminal(nonTerminal)) {
            // 对于每个产生式 A -> alpha
            // 对于First(alpha)中的每个终结符'a'
            for (const auto& terminal : firstSetsMap[production]) {
                // 在LL(1)分析表的M[A, a]中添加A -> alpha
                LL1Table->addEntry(nonTerminal, terminal, production);
            }

            // 如果ε在First(alpha)中，对于Follow(A)中的每个元素'b'，在LL(1)分析表的M[A, b]中添加A -> alpha
            if (haveEpsilon(firstSetsMap[production])) {
                for (const auto& terminal : followSetsMap[nonTerminal]) {
                    LL1Table->addEntry(nonTerminal, terminal, production);
                }
            }
        }
    }
}

void LL1Parser::reduceResultStack(){
    LL1AnalysisNode lastNon_terminalNode;
    bool haveLastNon_terminalNode = false;
    std::vector<LL1AnalysisNode> FinalStack;
    //find the last Non_terminal;
    for(auto symbolNode = resultStack.rbegin(); 
    symbolNode != resultStack.rend(); ++symbolNode){
        if((*symbolNode).isFinal){
            FinalStack.push_back(*symbolNode);
            haveLastNon_terminalNode = true;
        } else {
            lastNon_terminalNode = *symbolNode;
            break;
        }
    }
    if(!lastNon_terminalNode)
        return;
    //judge if can reduce
    if(lastNon_terminalNode.production.size() != FinalStack.size()){
        return;
    }
    //check error
    if(lastNon_terminalNode.production == FinalStack){
        newAnalysisNode = buildAnalysisNode_final_non_terminal(
        lastNon_terminalNode,FinalStack);
        //erase old
        for (auto symbolNode = resultStack.rbegin(); 
            symbolNode != resultStack.rend(); ++symbolNode) {
            if (*symbolNode == lastNon_terminalNode) {
                resultStack.erase(symbolNode.base(), resultStack.end());
                break;
            }
        }
        symbolNode.push_back(newAnalysisNode);
    } else {
        std::cerr << "lastNon_terminalNode match error"
        <<std::endl;
        break;
    }
}

bool LL1Parser::parse(){
    parseStack.push_back(buildAnalysisNode_non_terminal(startSymbol));
    while (!parsingStack.empty() && 
    parsingTokenIndex < (*tokens).size()) {

        std::string stackTop = parseStack.top();
        //curToken: pair[Type,Exp]
        auto curToken = (*tokens)[parsingTokenIndex];

        //terminal
        if(terminals.find(stackTop)! = terminals.end()){
            //match
            if(curToken.First == stackTop){
                parseStack.pop();
                node = buildAnalysisNode_terminal(curToken);
                resultStack.push(node);
                reductionResultStack();
            }
            else{//error detaction
                std::cerr << "terminal Failed at token num " <<
                << parsingTokenIndex <<" : ["<<
                curToken.first<<", "<<curToken.second<<
                " ]"<<std::endl;
                return false;
            }
            parsingTokenIndex++;
        //non_terminal
        } else if(non_terminals.find(stackTop) != non_terminals.end()){
            ll1TableEntry entryMap = (*LL1Table)[stackTop];
            //match
            if(entryMap.find(curToken.First) != entryMap.end()){
                parseStack.pop();
                for(const auto& symbol : entryMap[curToken.First]){
                    parseStack.push(symbol);
                }
                node = buildAnalysisNode_non_terminal(stackTop,entryMap[curToken.First]);
                resultStack.push(node);
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