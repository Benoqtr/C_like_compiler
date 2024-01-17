namespace LL1{

//tokenPtr
using tokensPtr = grammar::tokensPtr

using ASTRoot = grammar::ASTRoot;

//map non_terminal symbol to all its production lists 
using productionMapPtr = config::productionMapPtr;

//several grammar symbols
using productionContext = std::vector<std::string>;

//map forward symbol to a specific production list for each non_terminal symbol
using ll1TableEntry = std::map<std::string,productionContext>;

//ll1 analysis table
//table contains all non_terminal entry which 
// map forward symbol to a specific production list for each non_terminal symbol
using ll1tablePtr = std::shared_ptr<std::map<std::string,ll1TableEntry>>;

//map string to a set of strings
//example StatementList: {ID,if,return,while,ε}
using setsMap = std::map<std::string,std::set<std::string>>;

//struct to hold essencial info throughout the
//grammar analysis
//recive productionMapPtr
class LL1grammarInfo{
public:
    productionMapPtr productionMap;
    std::set<std::string> terminals;
    std::set<std::string> non_terminals;
    std::string startSymbol;

    grammarInfo(productionMapPtr productionMap);
private:
    void initTerminalSet();
    void initNon_terminalSet();
};

class LL1TableConstructor{
    public:
        productionMapPtr productionMap;
        LL1TableConstrucor(const LL1grammarInfo& grammarInfo);
        ll1tablePtr getll1Table();
    private:
        LL1grammarInfo& grammarInfo;
        setsMap firstSetsMap;
        setsMap followSetsMap;
        ll1tablePtr LL1Table;
        
        void calculateFirstSet();
        void calculateFollowSet();
        void constructLL1Table();
        bool tryAddNewSymbol();
}

//stack element when generating ASTree
class LL1AnalysisNode{
public:
    bool isFinal;
    std::string symbolName;
    std::vector<std::string> production;
    std::shared_ptr<AST::baseAST> ASTnode;
}

class LL1Parser{
public:
    LL1Parser();
private:
    LL1grammarInfo grammarInfo;
    int parsingTokenIndex;
    tokensPtr tokens;
    ll1tablePtr LL1Table;
    //stack for matching
    std::stack<std::string> parseStack;//add start/tem
    //stack for generating
    std::vector<LL1AnalysisNode> resultStack;

    LL1AnalysisNode buildAnalysisNode_terminal()
    LL1AnalysisNode buildAnalysisNode_non_terminal()
    LL1AnalysisNode buildAnalysisNode_final_non_terminal()
    void reduceResultStack();
    void parse();
};

class LL1Constructor{
public:
    LL1Constructor(const LL1grammarInfo& grammarInfo,
    tokensPtr tokens):grammarInfo(grammarInfo),tokens(tokens){};
    std::shared_ptr<ProgramAST> getASTree();
private:
    std::shared_ptr<LL1grammarInfo> grammarInfo;
    tokensPtr tokens;
    ll1tablePtr LL1Table;
    std::shared_ptr<ProgramAST> ASTree;
    stack;

    void genTree();
    void genTable();
    void parse();
};

}
