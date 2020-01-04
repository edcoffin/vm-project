#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <fstream>
#include <time.h>

#include "simple.hpp"

/* Un comment to enable debug output */
//#define DEBUG_OUTPUT

static void
printString(int64_t stringPointer)
   {
   #define PRINTSTRING_LINE LINETOSTR(__LINE__)
   char *strPtr = (char *)stringPointer;
   fprintf(stderr, "%s", strPtr);
   }

static void
printInt32(int32_t value)
   {
   #define PRINTINT32_LINE LINETOSTR(__LINE__)
   fprintf(stderr, "%d", value);
   }

SimpleMethod::SimpleMethod(OMR::JitBuilder::TypeDictionary *types)
   : OMR::JitBuilder::MethodBuilder(types)
   {
   DefineLine(LINETOSTR(__LINE__));
   DefineFile(__FILE__);

   DefineName("increment");
   DefineParameter("value", Int32);
   DefineReturnType(Int32);
}

static const char *prefix="increment(";
static const char *middle=") = ";
static const char *suffix="\n";

bool
SimpleMethod::buildIL()
   {
   Return(
      Add(
         Load("value"),
         ConstInt32(1)));

   return true;
   }

int32_t 
SimpleMethod::jit_compile_function(bool run_function, 
                     int32_t n, 
                     int32_t count) {
   bool initialized = initializeJit();
   if (!initialized)
      {
      fprintf(stderr, "FAIL: could not initialize JIT\n");
      exit(-1);
      }

   OMR::JitBuilder::TypeDictionary types;

   SimpleMethod method(&types);
   void *entry=0;
   int32_t rc = compileMethodBuilder(&method, &entry);

   if (rc != 0)
   {
      fprintf(stderr,"FAIL: compilation error %d\n", rc);
      exit(-2);
   }

   int32_t result = 0;

   if(run_function) {
      for(int i = 0; i < count; i++) {
         SimpleFunctionType *increment = (SimpleFunctionType *)entry;
         result += increment(20);
      }
   }

   shutdownJit();

   return result;
}

int
SimpleMethod::run(int n) {
   bool initialized = initializeJit();
   if (!initialized)
      {
      fprintf(stderr, "FAIL: could not initialize JIT\n");
      exit(-1);
      }

   OMR::JitBuilder::TypeDictionary types;

   SimpleMethod method(&types);
   void *entry=0;
   int32_t rc = compileMethodBuilder(&method, &entry);
   if (rc != 0)
      {
      fprintf(stderr,"FAIL: compilation error %d\n", rc);
      exit(-2);
      }

   SimpleFunctionType *increment = (SimpleFunctionType *)entry;
   int32_t result = increment(20);

   shutdownJit();

   return result;
}