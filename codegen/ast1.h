#pragma once
#include <queue>
#include <string>
#include <map>
/// ExprAST - Base class for all expression nodes.
class ExprAST {
public:
  virtual ~ExprAST() = default;

  virtual Value *codegen() = 0;
};

/// DeclAST - basic compoment of program
class DeclAST : public ExprAST {
public:
  virtual ~ExprAST() = default;

  virtual Value *codegen() = 0;
};

/// Global Variable Declaration
class GloVarDeclAst : public DeclAST {
    std::string varType;
    std::string name;
public:
    GloVarDeclAst(std::string varType,std::string name)
    : varType(varType), name(name) {}
    Value *codegen() override;
};

/// StatAST - basic compoment of function
class StatAST : public ExprAST {
public:
  virtual ~ExprAST() = default;

  virtual Value *codegen() = 0;
};

/// 1/5 StatAST: Expression
class ExprStatAst : public StatAST {
    std::string varType;
    std::string name;
public:
    GloVarDeclAst(std::string varType,std::string name)
    : varType(varType), name(name) {}
    Value *codegen() override;
};

/// 2/5 StatAST: Selection
class ExprStatAst : public StatAST {
    std::string varType;
    std::string name;
public:
    GloVarDeclAst(std::string varType,std::string name)
    : varType(varType), name(name) {}
    Value *codegen() override;
};

/// 3/5 StatAST: Iteration
class ExprStatAst : public StatAST {
    std::string varType;
    std::string name;
public:
    GloVarDeclAst(std::string varType,std::string name)
    : varType(varType), name(name) {}
    Value *codegen() override;
};

/// 4/5 StatAST: Return
class ExprStatAst : public StatAST {
    std::string varType;
    std::string name;
public:
    GloVarDeclAst(std::string varType,std::string name)
    : varType(varType), name(name) {}
    Value *codegen() override;
};

/// 5/5 StatAST: Invoke
class ExprStatAst : public StatAST {
    std::string varType;
    std::string name;
public:
    GloVarDeclAst(std::string varType,std::string name)
    : varType(varType), name(name) {}
    Value *codegen() override;
};

/// Function Declaration
class FunctionAst : public DeclAST {
    std::string retType;
    std::string name;
    std::queue<map<std::string,std::string>> ParameterList;
    std::queue<StatAST> statList;
public:
    FunctionAst(std::string retType,
    std::string name,
    std::queue<map<std::string,std::string>> ParameterList,
    std::queue<StatAST> statList)
    : retType(retType), name(name),
    ParameterList(ParameterList), statList(statList){}
    Value *codegen() override;
};

/// ProgramAST - Toppest ASTnode only contains DeclAST
class ProgramAST : public ExprAST {
  std::queue<DeclAST> declList

public:
  ProgramAST(DeclAST declAST){
    declList.push(declAST);
  }

  Value *codegen() override;
};

/// NumberExprAST - Expression class for numeric literals like "1.0".
class NumberExprAST : public ExprAST {
  double Val;

public:
  NumberExprAST(double Val) : Val(Val) {}

  Value *codegen() override;
};

/// VariableExprAST - Expression class for referencing a variable, like "a".
class VariableExprAST : public ExprAST {
  std::string Name;

public:
  VariableExprAST(const std::string &Name) : Name(Name) {}

  Value *codegen() override;
};

/// BinaryExprAST - Expression class for a binary operator.
class BinaryExprAST : public ExprAST {
  char Op;
  std::unique_ptr<ExprAST> LHS, RHS;

public:
  BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS,
                std::unique_ptr<ExprAST> RHS)
      : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}

  Value *codegen() override;
};

/// CallExprAST - Expression class for function calls.
class CallExprAST : public ExprAST {
  std::string Callee;
  std::vector<std::unique_ptr<ExprAST>> Args;

public:
  CallExprAST(const std::string &Callee,
              std::vector<std::unique_ptr<ExprAST>> Args)
      : Callee(Callee), Args(std::move(Args)) {}

  Value *codegen() override;
};

/// PrototypeAST - This class represents the "prototype" for a function,
/// which captures its name, and its argument names (thus implicitly the number
/// of arguments the function takes).