namespace AST{

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