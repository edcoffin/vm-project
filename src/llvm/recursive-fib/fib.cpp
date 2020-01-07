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

  // Get pointers to the constants.
  Value *One = ConstantInt::get(Type::getInt32Ty(Context), 1);
  Value *Two = ConstantInt::get(Type::getInt32Ty(Context), 2);

  // Get pointer to the integer argument of the add1 function...
  Argument *ArgX = &*FibF->arg_begin(); // Get the arg.
  ArgX->setName("AnArg");            // Give it a nice symbolic name for fun.

  // Create the true_block.
  BasicBlock *RetBB = BasicBlock::Create(Context, "return", FibF);
  // Create an exit block.
  BasicBlock* RecurseBB = BasicBlock::Create(Context, "recurse", FibF);

  // Create the "if (arg <= 2) goto exitbb"
  Value *CondInst = new ICmpInst(*BB, ICmpInst::ICMP_SLE, ArgX, Two, "cond");
  BranchInst::Create(RetBB, RecurseBB, CondInst, BB);

  // Create: ret int 1
  ReturnInst::Create(Context, One, RetBB);

  // create fib(x-1)
  Value *Sub = BinaryOperator::CreateSub(ArgX, One, "arg", RecurseBB);
  CallInst *CallFibX1 = CallInst::Create(FibF, Sub, "fibx1", RecurseBB);
  //CallFibX1->setTailCall();

  // create fib(x-2)
  Sub = BinaryOperator::CreateSub(ArgX, Two, "arg", RecurseBB);
  CallInst *CallFibX2 = CallInst::Create(FibF, Sub, "fibx2", RecurseBB);
  //CallFibX2->setTailCall();

  // fib(x-1)+fib(x-2)
  Value *Sum = BinaryOperator::CreateAdd(CallFibX1, CallFibX2,
                                         "addresult", RecurseBB);

  // Create the return instruction and add it to the basic block
  ReturnInst::Create(Context, Sum, RecurseBB);

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

int32_t testThroughput(std::ostream &ostream, 
                    int32_t s_to_run, 
                    int32_t ns_to_run) {
                  
  int32_t ONE_BILLION=1000000000;

  struct timespec begin, current, elapsed;

  clock_gettime(CLOCK_MONOTONIC_RAW, &begin);

  elapsed.tv_sec = 0;
  elapsed.tv_nsec = 0;

  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  LLVMContext Context;

  // Create some module to put our function into it.
  std::unique_ptr<Module> Owner(new Module("test", Context));
  Module *M = Owner.get();

  // We are about to create the "fib" function:
  Function *FibF = CreateFibFunction(M, Context);

  // Now we going to create JIT
  std::string errStr;
  ExecutionEngine *EE =
    EngineBuilder(std::move(Owner))
    .setErrorStr(&errStr)
    .create();

  // Call the Fibonacci function with argument n:
  std::vector<GenericValue> Args(1);
  Args[0].IntVal = APInt(32, 20);

  while(elapsed.tv_sec * ONE_BILLION + elapsed.tv_nsec < s_to_run * ONE_BILLION + ns_to_run) {
    GenericValue GV = EE->runFunction(FibF, Args);
    clock_gettime(CLOCK_MONOTONIC_RAW, &current);
    elapsed.tv_sec = current.tv_sec - begin.tv_sec;
    elapsed.tv_nsec = current.tv_nsec - begin.tv_nsec;
    ostream << elapsed.tv_sec * ONE_BILLION + elapsed.tv_nsec << std::endl;
  }

  return 0;

}