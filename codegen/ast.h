namespace AST{

//This help to use a string to invoke different ASTNode constuctor
std::unique_ptr<BaseAST> newASTNode(const std::string& type,
    const std::vector<std::string>& production){
        switch(type) {
            case BaseAST:
                return std::make_unique<BaseAST>(type,production);
            default:
                return std::make_unique<BaseAST>(type,production);
        }
    }

// BaseAST - Base class for all expression nodes.
class BaseAST {
public:
    std::string type;

    BaseAST(const std::string& type,
    const std::vector<std::string>& production)

    virtual ~ExprAST() = default;

    virtual IR::IRmsg *codegen() = 0;
private:
    //must be the specific production
    std::vector<std::string> production;

    std::vector<std::shared_ptr<BaseAST>> childAST;

};
}