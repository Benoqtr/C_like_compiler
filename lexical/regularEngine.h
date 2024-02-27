#pragma once
#include <memory>

namespace regularEngine{

//map type to its regular Expression
using reExpressionsMapPtr = std::shared_ptr<std::map<std::string,std::string>>;

class DFAnode {
public:
    int id;
    int eid;
    int trascnt;
    int EPStrascnt;
    int totaltrascnt;
    std::map<char,int> transitions;
    std::set<int> EPStransitions;
    bool isAcceptable;

    DFAnode(int _id, int _edi);
    void addTransition(char c, int s);
    void addTransition(int s);
};

class ThompsonConstruction {//construct NFA
public:
    ThompsonConstruction() = default;
    std::vector<DFAnode> buildNFA(const std::string& postfixRegex);

private:
    std::vector<DFAnode> states;
    int stateIdCounter = 0;

    std::stack<int> operandStack;

    void pushConcatenation();
    void pushUnion();
    void pushStar();
    void pushSymbol(char symbol);
};

class DFA{
public:
    std::string postfixRegex;
    std::vector<DFAnode> nodes;

    DFA(const std::string& postfixRegex):
    postfixRegex(postfixRegex){}
    std::string ismatch(std::string raw_token);
private:
    void NFAConstruction(){};
    void DFAConstruction(){};
    void minimizeDFA(){};
}

class regularEngine{
public:
    regularEngine(const reExpressionsMapPtr& REConfig);
    std::string getType(const std::string& raw_token);
private:
    std::shared_ptr<map<std::string, std::shared_ptr<DFA>>> typeAndDFA;
    std::string infixToPostExpr(const std::string& regularExpr);
    std::string expressionExpand(const std::string& regularExpr);
    std::shared_ptr<DFA> getDFA(const std::string& regularExpr);
};

}