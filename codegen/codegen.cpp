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
    //DeclarationList -> EPSION
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

// // 定义条件语句的函数
// Function* createConditionalFunction() {
//     // 函数签名：int conditionalFunction(int)
//     FunctionType* FuncType = FunctionType::get(Type::getInt32Ty(TheContext), {Type::getInt32Ty(TheContext)}, false);
//     Function* Func = Function::Create(FuncType, Function::ExternalLinkage, "conditionalFunction", TheModule);

//     // 创建函数的基本块
//     BasicBlock* EntryBB = BasicBlock::Create(TheContext, "entry", Func);
//     Builder.SetInsertPoint(EntryBB);

//     // 函数参数
//     Argument* ArgX = &*Func->arg_begin();
//     ArgX->setName("x");

//     // 在条件块内部定义变量
//     Value* InternalVar = Builder.CreateAlloca(Type::getInt32Ty(TheContext), nullptr, "internalVar");

//     // 条件语句
//     Value* Condition = Builder.CreateICmpSGT(ArgX, ConstantInt::get(TheContext, APInt(32, 0)), "compare");
//     Builder.CreateCondBr(Condition, EntryBB, EntryBB);

//     // 在条件块中使用变量
//     Builder.SetInsertPoint(EntryBB);
//     Builder.CreateStore(ConstantInt::get(TheContext, APInt(32, 42)), InternalVar);

//     // 将条件块内部定义的变量赋值给外部变量
//     ExternalVar = InternalVar;

//     // 返回值
//     Builder.CreateRet(ExternalVar);

//     return Func;
// }

// ParameterList
// Parameter
// CompoundStatement
// StatementList
// Statement