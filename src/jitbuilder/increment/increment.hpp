#ifndef INCREMENT_INCL
#define INCREMENT_INCL

#include "JitBuilder.hpp"
#include <iostream>



typedef int32_t (IncrementFunctionType)(int32_t);

class IncrementMethod : public OMR::JitBuilder::MethodBuilder
   {
   public:
   IncrementMethod(OMR::JitBuilder::TypeDictionary *types);
   virtual bool buildIL();
   static int32_t jit_compile_function(bool, int32_t, int32_t);
   };

#endif // !defined(SIMPLE_INCL)
