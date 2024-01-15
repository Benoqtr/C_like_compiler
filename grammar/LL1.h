namespace LL1{

//tokenPtr
using tokensPtr = std::shared_ptr<std::vector<
    std::pair<std::string,std::string>>>;

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

class LL1Constructor{
public:
    LL1Constructor(std::shared_ptr<LL1grammarInfo> grammarInfo,
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
}

class LL1TableConstructor{
    public:
        productionMapPtr productionMap;
        LL1TableConstrucor(productionMapPtr productionMap);
        ll1tablePtr getll1Table();
    private:
        setsMap firstSetsMap;
        setsMap followSetsMap;
        ll1tablePtr LL1Table;
        
        void calculateFirstSet();
        void calculateFollowSet();
        void constructLL1Table();
        bool tryAddNewSymbol();
}

class LL1Parser{
public:
    ll1tablePtr LL1Table;
    std::stack<std::string> parseStack;//add start/tem
    std::stack<std::pair<std::string,std::string>> resultStack;
    tokensPtr tokens;
    int parsingTokenIndex;
    reductionResultStack()
}
private:
    ASTnode* buildASTnode();
    void parse();
        parseStack
        tokens

}

void LL1Parser::parse(){
    push startSymbol
    while (parseStack.top!="$" && tokens.second() != "$") // 如果输入串和栈都非空{
        if(parseStack.top() is t)
    }
if the top of the parsing stack is terminal a and the next input token = a // 如果栈顶是终结符号a
then // 匹配
pop the parsing stack; // 弹出元素
advance the input; // 输入串吃掉一个字符
else if (the top of the parsing stack is non-terminal A // 如果栈顶是非终结符号A
and the next input token is terminal a // 下一个符号是a
and parsing table entry M[A,a] contains production A→X1X2…Xn) // 分析表中M[A,a]包含规则
then // 生成
pop the parsing stack; // 弹出栈顶元素
for i:=n downto 1 do // 从右向左将表达式压栈
push Xi onto the parsing stack;
else error;
if (the top of the parsing stack = $ and the next input token = $) then accept // 如果输入串和栈都空
else err
}