#ifndef RECURSIVEFIB_INCL
#define RECURSIVEFIB_INCL

#include "JitBuilder.hpp"

typedef int32_t (RecursiveFibFunctionType)(int32_t);

class RecursiveFibonnaciMethod : public OMR::JitBuilder::MethodBuilder
   {
   public:
   RecursiveFibonnaciMethod(OMR::JitBuilder::TypeDictionary *types);
   virtual bool buildIL();
   static int run(int32_t);
   };

#endif // !defined(RECURSIVEFIB_INCL)
