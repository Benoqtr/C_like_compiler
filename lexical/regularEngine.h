namespace regularEngine{

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
    std::vector<DFAnode> buildNFA(std::string postfixRegex);

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
    DFA(std::string postfixRegex)
    std::string ismatch(std::string raw_token)
private:
    std::vector<DFAnode> nodes;
    void NFAConstruction(){};
    void DFAConstruction(){};
    void minimizeDFA(){};
}

class regularEngine{
public:
    regularEngine(const std::string& fileName)
    std::string getType(std::string token)
private:
    std::unique_ptr<map<std::string, std::string>> typeAndExpr;
    std::unique_ptr<map<std::string, std::shared_ptr<DFA>>> typeAndDFA;
private:
    std::unique_ptr<std::map<std::string, std::string>> getRegularInfo(const std::string& fileName)
    void infixToPostExpr(){};
    std::shared_ptr<DFA> getDFA(std::string regularExpr)
    bool is_matched(std::string token,std::shared_ptr<DFA> DFA)
};

}