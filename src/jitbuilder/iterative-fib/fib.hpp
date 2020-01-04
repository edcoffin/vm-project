#ifndef IterativeFIB_INCL
#define IterativeFIB_INCL

#include "JitBuilder.hpp"
#include <iostream>

typedef int32_t (IterativeFibFunctionType)(int32_t);

class IterativeFibonnaciMethod : public OMR::JitBuilder::MethodBuilder
   {
   public:
   IterativeFibonnaciMethod(OMR::JitBuilder::TypeDictionary *types);
   virtual bool buildIL();
   static int run(int32_t);
   static int32_t jit_compile_function(bool, int32_t, int32_t);
   static void testThroughput(std::ostream&, int32_t, int32_t);
   };

#endif // !defined(IterativeFIB_INCL)
