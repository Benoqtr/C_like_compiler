//This file complement the codegen override of each derive class

//Excute at the begining of IR generating.
ProgramAST::InitializeModule() {
  // Open a new context and module.
  TheContext = std::make_unique<LLVMContext>();//global
  TheModule = std::make_unique<Module>("TheModule", *TheContext);

  // Create a new builder for the module.
  Builder = std::make_unique<IRBuilder<>>(*TheContext);
}

////vector<BaseAST*> childAST
//Toppest codegen
//Program -> DeclarationList
ProgramAST::codegen(){
    InitializeModule();
    //DeclarationListAST
    childAST[0]->codegen()
}

DeclarationListAST::codegen(){
    //DeclarationList -> ε
    // if(childAST[0])
    //     return
    //
    //
    //DeclarationList -> Declaration DeclarationList
    childAST[0] -> codegen();
    childAST[1] -> codegen();

}

DeclarationAST::codegen(){
    //Declaration -> VariableDeclaration
    childAST[0] -> codegen();
    //Declaration -> FunctionDeclaration
    childAST[0] -> codegen();
}

VariableDeclarationAST::codegen(){
    IR:msg _type, _ID;
    //VariableDeclaration -> int ID ;
    //Although int only, keep possibility for future extend
    _type = childAST[0] -> codegen();
    _ID = childAST[1] -> codegen();
    //type
    Type* IntType = Type::getInt32Ty(TheContext);
    //type
    ID = _ID.exp;
    //the memory managed by TheModule
    new GlobalVariable(
        TheModule,      // 所属模块
        IntType,        // 变量类型
        false,          // 是否是常量
        GlobalValue::ExternalLinkage, // 链接方式，声明为外部可见
        nullptr,        // 初始值（如果有）
        ID              // 变量名称
    );
}

FunctionDeclaration::codegen(){
    //FunctionDeclaration -> int ID ( ParameterList ) 
    //CompoundStatement ;
    _type = childAST[0] -> codegen();
    _ID = childAST[1] -> codegen();
    _ParameterList = childAST[3] -> codegen();
    childAST[5] -> codegen();
    // llvm::FunctionType* ReturnType = llvm::FunctionType::get(builder.getInt32Ty(), false);
    // while(!ParameterList.empty){
        
    // }
    // llvm::Type* paramTypes[] = {intType, doubleType};
    // llvm::ArrayRef<llvm::Type*> params(paramTypes);
    // llvm::Function* mainFunction = llvm::Function::Create(mainFunctionType, llvm::Function::ExternalLinkage, "main", &module);
    // llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(context, "entry", mainFunction);
    // builder.SetInsertPoint(entryBlock);

    // llvm::Value* loadedGlobalVar = builder.CreateLoad(globalVar);
    // builder.CreateRet(loadedGlobalVar);
}

// ParameterList
// Parameter
// CompoundStatement
// StatementList
// Statement