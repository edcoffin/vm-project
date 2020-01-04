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
#include "simple.hpp"

using namespace llvm;

static Function *CreateSimpleFunction(Module *M, LLVMContext &Context) {
  // Create the Simple function and insert it into module M. This function is said
  // to return an int and take an int parameter.
  FunctionType *SimpleFTy = FunctionType::get(Type::getInt32Ty(Context),
                                           {Type::getInt32Ty(Context)}, false);
  Function *SimpleF =
      Function::Create(SimpleFTy, Function::ExternalLinkage, "increment", M);

  // Add a basic block to the function.
  BasicBlock *BB = BasicBlock::Create(Context, "EntryBlock", SimpleF);

  // Get pointers to the constants.
  Value *One = ConstantInt::get(Type::getInt32Ty(Context), 1);
  
  // Get pointer to the integer argument of the add1 function...
  Argument *ArgX = &*SimpleF->arg_begin(); // Get the arg.
  ArgX->setName("AnArg");            // Give it a nice symbolic name for fun.

  // Simple(x-1)+Simple(x-2)
  Value *Sum = BinaryOperator::CreateAdd(ArgX, One,
                                         "addresult", BB);

  // Create the return instruction and add it to the basic block
  ReturnInst::Create(Context, Sum, BB);

  return SimpleF;
}

int32_t jit_compile_function(bool run_function, int32_t n, int32_t count) {
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  LLVMContext Context;

  // Create some module to put our function into it.
  std::unique_ptr<Module> Owner(new Module("test", Context));
  Module *M = Owner.get();

  // We are about to create the "Simple" function:
  Function *_SimpleF = CreateSimpleFunction(M, Context);

  // Now we going to create JIT
  std::string errStr;
  ExecutionEngine *_EE =
    EngineBuilder(std::move(Owner))
    .setOptLevel(CodeGenOpt::Aggressive)
    .setErrorStr(&errStr)
    .create();

  int32_t sum = 0;

  // trigger the compilation
  uint64_t ptr = _EE->getFunctionAddress("increment"); 

  if(run_function) {
    std::vector<GenericValue> Args(1);
    Args[0].IntVal = APInt(32, n);
    for(int i = 0; i < count; i++) {
      GenericValue GV = _EE->runFunction(_SimpleF, Args);
      sum += GV.IntVal.getSExtValue();
    }
  }

  return sum;

}

int simple(int32_t n) {
  
  InitializeNativeTarget();
  InitializeNativeTargetAsmPrinter();
  LLVMContext Context;

  // Create some module to put our function into it.
  std::unique_ptr<Module> Owner(new Module("test", Context));
  Module *M = Owner.get();

  // We are about to create the "Simple" function:
  Function *SimpleF = CreateSimpleFunction(M, Context);

  // Now we going to create JIT
  std::string errStr;
  ExecutionEngine *EE =
    EngineBuilder(std::move(Owner))
    .setOptLevel(CodeGenOpt::Aggressive)
    .setErrorStr(&errStr)
    .create();

  // Call the Simpleonacci function with argument n:
  std::vector<GenericValue> Args(1);
  Args[0].IntVal = APInt(32, n);
  GenericValue GV = EE->runFunction(SimpleF, Args);

  // useful for printing disassembly in GDB
  uint64_t ptr = EE->getFunctionAddress("increment"); 

  return (int32_t) GV.IntVal.getSExtValue();

}