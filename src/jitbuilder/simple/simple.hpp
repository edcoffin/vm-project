#ifndef SIMPLE_INCL
#define SIMPLE_INCL

#include "JitBuilder.hpp"
#include <iostream>



typedef int32_t (SimpleFunctionType)(int32_t);

class SimpleMethod : public OMR::JitBuilder::MethodBuilder
   {
   public:
   SimpleMethod(OMR::JitBuilder::TypeDictionary *types);
   virtual bool buildIL();
   static int run(int32_t);
   static int32_t jit_compile_function(bool, int32_t, int32_t);
   };

#endif // !defined(SIMPLE_INCL)
