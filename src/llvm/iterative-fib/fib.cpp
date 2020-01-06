#include "llvm/ADT/APInt.h"
#include "llvm/IR/Verifier.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/ExecutionEngine/MCJIT.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include <algorithm>
#include <cstdlib>
#include <memory>
#include <string>
#include <vector>

#include <fstream>
#include <time.h>
#include "fib.hpp"

using namespace llvm;

static Function *CreateFibFunction(Module *M, LLVMContext &Context) {
  // Create the fib function and insert it into module M. This function is said
  // to return an int and take an int parameter.
  FunctionType *FibFTy = FunctionType::get(Type::getInt32Ty(Context),
                                           {Type::getInt32Ty(Context)}, false);
  Function *FibF =
      Function::Create(FibFTy, Function::ExternalLinkage, "fib", M);

  // Add a basic block to the function.
  BasicBlock *BB = BasicBlock::Create(Context, "EntryBlock", FibF);

  IRBuilder<> Builder(Context);
  Builder.SetInsertPoint(BB);

  // Get pointers to the constants.
  Value *Zero = ConstantInt::get(Type::getInt32Ty(Context), 0);
  Value *One = ConstantInt::get(Type::getInt32Ty(Context), 1);
  Value *Five = ConstantInt::get(Type::getInt32Ty(Context), 5);

  // Get pointer to the integer argument of the add1 function...
  Argument *ArgX = &*FibF->arg_begin(); // Get the arg.
  ArgX->setName("AnArg");            // Give it a nice symbolic name for fun.

  // Create the return 0 if n == 0
  //BasicBlock *RetBB = BasicBlock::Create(Context, "return", FibF);
  // Create: ret int 0
  //ReturnInst::Create(Context, Zero, RetBB);

  // Create the "if (arg == 0) return"
  //Value *CondInst = new ICmpInst(*BB, ICmpInst::ICMP_EQ, ArgX, Zero, "cond");
  //BranchInst::Create(RetBB, CondInst);
  
  AllocaInst *last_sum_alloc_ptr = new AllocaInst(Type::getInt32Ty(Context), 0,"last_sum", BB);
  AllocaInst *sum_alloc_ptr = new AllocaInst(IntegerType::getInt32Ty(Context), 0, "sum", BB);
  AllocaInst *temp_alloc_ptr = new AllocaInst(IntegerType::getInt32Ty(Context), 0, "temp", BB);

  StoreInst *last_sum_store = new StoreInst(Zero, last_sum_alloc_ptr, false, BB);
  StoreInst *sum_store = new StoreInst(One, sum_alloc_ptr, false, BB);
  StoreInst *temp_store = new StoreInst(Zero, temp_alloc_ptr, false, BB);
   

  BasicBlock *LoopBB = BasicBlock::Create(Context, "loop", FibF);
  BasicBlock *AfterBB = BasicBlock::Create(Context, "afterloop", FibF);
  
  BasicBlock *PreheaderBB = Builder.GetInsertBlock();
  Builder.CreateBr(LoopBB);
  Builder.SetInsertPoint(LoopBB);
  PHINode *IndVar = Builder.CreatePHI(Type::getInt32Ty(Context), 2, "i");
  
  // Loop Start Value is 1
  IndVar->addIncoming(One, PreheaderBB);

  // https://stackoverflow.com/questions/29223589/how-would-i-create-this-sequence-in-the-llvm-builder-framework
  // body of loop
  auto* sum = Builder.CreateLoad(sum_alloc_ptr);
  auto* last_sum = Builder.CreateLoad(last_sum_alloc_ptr);
  auto* temp_sum = Builder.CreateAdd(sum, last_sum, "temp_sum");

  Builder.CreateStore(temp_sum, temp_alloc_ptr, false);
  Builder.CreateStore(sum, last_sum_alloc_ptr, false);
  Builder.CreateStore(temp_sum, sum_alloc_ptr, false);

  //Value *Add = Builder.CreateAdd(One, Builder.getInt32(5), "tmp");
  
  Value *NextVal = Builder.CreateAdd(IndVar, One, "nextval");
  Value *EndCond = Builder.CreateICmpNE(IndVar, ArgX, "loopcond");

  BasicBlock *LoopEndBB = Builder.GetInsertBlock();
  Builder.CreateCondBr(EndCond, LoopBB, AfterBB);
  Builder.SetInsertPoint(AfterBB);
  IndVar->addIncoming(NextVal, LoopEndBB);
  
  Builder.CreateRet(Builder.CreateLoad(sum_alloc_ptr));
    
  return FibF;
}

int32_t jit_compile_function(bool run_function, int32_t n, int32_t count) {
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  LLVMContext Context;

  // Create some module to put our function into it.
  std::unique_ptr<Module> Owner(new Module("test", Context));
  Module *M = Owner.get();

  // We are about to create the "fib" function:
  Function *_FibF = CreateFibFunction(M, Context);

  llvm::PassBuilder _PassBuilder;
  
  auto _LoopMgr = llvm::LoopAnalysisManager();
  auto _CGSCCMgr = llvm::CGSCCAnalysisManager();
  auto _ModMgr = llvm::ModuleAnalysisManager();
  auto _FAMgr = llvm::FunctionAnalysisManager(); // magic: it's must be here

  _PassBuilder.registerModuleAnalyses(_ModMgr);
  // search call graph for strongly connected components
  _PassBuilder.registerCGSCCAnalyses(_CGSCCMgr);
  _PassBuilder.registerFunctionAnalyses(_FAMgr);
  _PassBuilder.registerLoopAnalyses(_LoopMgr);

  _PassBuilder.crossRegisterProxies(_LoopMgr, _FAMgr, _CGSCCMgr, _ModMgr);

  auto _FunctionPassMgr = _PassBuilder.buildFunctionSimplificationPipeline(
        llvm::PassBuilder::OptimizationLevel::O3,
        llvm::PassBuilder::ThinLTOPhase::None,
        false);

  _FunctionPassMgr.run(*_FibF, _FAMgr);  

  // Now we going to create JIT
  std::string errStr;
  ExecutionEngine *_EE =
    EngineBuilder(std::move(Owner))
    .setOptLevel(CodeGenOpt::Aggressive)
    .setErrorStr(&errStr)
    .create();

  int32_t sum = 0;

  // trigger the compilation
  uint64_t ptr = _EE->getFunctionAddress("fib"); 

  if(run_function) {
    std::vector<GenericValue> Args(1);
    Args[0].IntVal = APInt(32, n);
    for(int i = 0; i < count; i++) {
      GenericValue GV = _EE->runFunction(_FibF, Args);
      sum += GV.IntVal.getSExtValue();
    }
  }

  return sum;

}