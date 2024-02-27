#include "regularEngine.h"

namespace regularEngine{

//--------------------------------------------------------------------------------
// 
// class DFAnode
// 
// 
// 
// 
// 
//--------------------------------------------------------------------------------
DFAnode::DFAnode(int _id, int _edi) : id(_id),eid(_edi) {
    isAcceptable = false;
    trascnt = 0;
    EPStrascnt = 0;
    totaltrascnt = 0;
}

//add normal Transition
void DFAnode::addTransition(char ch, int state){
    transitions[ch] = state;
    trascnt++;
    totaltrascnt++;
}

//add EPStransitions
void DFAnode::addTransition(int s){
    EPStransitions.insert(s);
    EPStrascnt++;
    totaltrascnt++;
}
//--------------------------------------------------------------------------------




//--------------------------------------------------------------------------------
// 
// class ThompsonConstruction
// 
// 
// 
// 
// 
//--------------------------------------------------------------------------------
std::vector<DFAnode> ThompsonConstruction::buildNFA(const std::string& postfixRegex) {
    for (char c : postfixRegex) {
        if (std::isalpha(c) || std::isdigit(c)) {
            pushSymbol(c);
        } else if (c == '.') {
            pushConcatenation();
        } else if (c == '|') {
            pushUnion();
        } else if (c == '*') {
            pushStar();
        }
    }

    if (operandStack.size() != 1) {
        std::cerr << "Invalid postfix regular expression." << std::endl;
        return {};
    }
    int finalOp = operandStack.top() ;
    states[states[finalOp].eid].isAcceptable = true ;

    return states;
}

void ThompsonConstruction::pushConcatenation() {
    int sndOp = operandStack.top();
    operandStack.pop();
    int fstOp = operandStack.top();
    operandStack.pop();

    states[states[fstOp].eid].addTransition(sndOp);
    states[fstOp].eid = states[sndOp].eid;

    operandStack.push(fstOp);

}

void ThompsonConstruction::pushUnion() {
    int sndOp = operandStack.top();
    operandStack.pop();
    int fstOp = operandStack.top();
    operandStack.pop();

    int bState = stateIdCounter++;
    int eState = stateIdCounter++;

    states.push_back(DFAnode(bState,eState));
    states.push_back(DFAnode(eState,eState));

    states[bState].addTransition(fstOp);
    states[bState].addTransition(sndOp);
    states[states[fstOp].eid].addTransition(eState);
    states[states[sndOp].eid].addTransition(eState);

    operandStack.push(bState);
}

void ThompsonConstruction::pushStar() {
    int Op = operandStack.top();
    operandStack.pop();

    int bState = stateIdCounter++;
    int eState = stateIdCounter++;

    states.push_back(DFAnode(bState, eState));
    states.push_back(DFAnode(eState, eState));

    states[bState].addTransition(Op);
    states[bState].addTransition(eState);

    states[states[Op].eid].addTransition(Op);
    states[states[Op].eid].addTransition(eState);

    operandStack.push(bState);
}

void ThompsonConstruction::pushSymbol(char symbol) {
    int bState = stateIdCounter++;
    int eState = stateIdCounter++;

    states.push_back(DFAnode(bState, eState));
    states.push_back(DFAnode(eState, eState));

    states[bState].addTransition(symbol,eState);

    operandStack.push(bState);

}
//--------------------------------------------------------------------------------






//--------------------------------------------------------------------------------
// 
// 
// 
// 
// class DFA
// 
//--------------------------------------------------------------------------------
std::string DFA::ismatch(std::string raw_token){};
void DFA::NFAConstruction(){
    ThompsonConstruction NFAConstructor();
    nodes = NFAConstructor.buildNFA(postfixRegex);
}
void DFA::DFAConstruction(){};
void DFA::minimizeDFA(){};

std::set<int> DFA::epsilonClosure(const std::set<int>& nfaStates) const {
    std::set<int> result = nfaStates;

    std::stack<int> stateStack;
    for (int nfaState : nfaStates) {
        stateStack.push(nfaState);
    }

    while (!stateStack.empty()) {
        int currentState = stateStack.top();
        stateStack.pop();

        for (int nextState : nodes[currentState].EPStransitions) {
            if (result.find(nextState) == result.end()) {
                result.insert(nextState);
                stateStack.push(nextState);
            }
        }
    }

    return result;
}
//--------------------------------------------------------------------------------



//--------------------------------------------------------------------------------
// 
// 
// 
// class regularEngine
// 
//--------------------------------------------------------------------------------

regularEngine::getType(const std::string& raw_token){
    for(const auto& pair : *typeAndDFA){
        std::shared_ptr<DFA> dfa = pair.second;
        if(dfa.ismatch(raw_token))
            return pair.first;
    }
    return "";
}

regularEngine::regularEngine(const reExpressionsMapPtr& REConfig){
    std::shared_ptr<DFA> dfa;
    for (const auto& pair : *REConfig) {
        dfa = getDFA(pair.second);
        typeAndDFA[pair.first] = dfa;
    std::cout << "REengine preprossing: TYPE: " << pair.first << std::endl;
    }
}

std::shared_ptr<DFA> getDFA(const std::string& regularExpr){
    std::string ExpandRegex, postfixRegex;
    ExpandRegex = expressionExpand(regularExpr);
    postfixRegex = infixToPostExpr(ExpandRegex);
    std::shared_ptr<DFA> dfa = std::make_shared<DFA>(postfixRegex);
    return dfa;
};

std::string expressionExpand(const std::string& regularExpr) {
    std::string expandedRegex;
    size_t pos = regularExpr.find('[');

    while (pos != std::string::npos) {
        size_t ppos = regularExpr.find(']', pos + 1);
        if (ppos == std::string::npos) {
            std::cerr << "Error: Missing closing bracket ']'." << std::endl;
            return "";
        }

        expandedRegex = "(";

        for (char i = regularExpr[pos + 1]; i <= regularExpr[ppos - 1]; ++i) {
            expandedRegex += i;
            if (i < regularExpr[ppos - 1]) {
                expandedRegex += '|';
            }
        }

        expandedRegex += ')';
        regularExpr = regularExpr.substr(0, pos) + expandedRegex + regularExpr.substr(ppos + 1);
        pos = regularExpr.find('[', pos + expandedRegex.size());
    }

    return regularExpr;
}

std::string infixToPostExpr(const std::string& regularExpr){
    auto getPrecedence = [](char op) -> int {
        if (op == '*' || op == '+')
            return 2;
        else if (op == '.' || op == '|')
            return 1;
        else
            return 0;
    };
    std::stack<char> operatorStack;
    std::string postfix;

    for (char ch : regularExpr) {
        switch (ch) {
            case '*':
            case '+':
            case '.':
                while (!operatorStack.empty() && getPrecedence(operatorStack.top()) >= getPrecedence(ch)) {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(ch);
                break;
            case '|':
                while (!operatorStack.empty() && getPrecedence(operatorStack.top()) >= getPrecedence(ch)) {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(ch);
                break;
            case '(':
                operatorStack.push(ch);
                break;
            case ')':
                while (!operatorStack.empty() && operatorStack.top() != '(') {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop();  // pop '('
                break;
            default:
                postfix += ch;
                break;
        }
    }

    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    return postfix;    
}
}//namespace regularEngine