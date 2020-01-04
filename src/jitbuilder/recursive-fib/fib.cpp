#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <fstream>
#include <time.h>

#include "fib.hpp"

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

RecursiveFibonnaciMethod::RecursiveFibonnaciMethod(OMR::JitBuilder::TypeDictionary *types)
   : OMR::JitBuilder::MethodBuilder(types)
   {
   DefineLine(LINETOSTR(__LINE__));
   DefineFile(__FILE__);

   DefineName("fib");
   DefineParameter("n", Int32);
   DefineReturnType(Int32);

   DefineFunction((char *)"printString",
                  (char *)__FILE__,
                  (char *)PRINTSTRING_LINE,
                  (void *)&printString,
                  NoType,
                  1,
                  Int64);
   DefineFunction((char *)"printInt32",
                  (char *)__FILE__,
                  (char *)PRINTINT32_LINE,
                  (void *)&printInt32,
                  NoType,
                  1,
                  Int32);
   }

static const char *prefix="fib(";
static const char *middle=") = ";
static const char *suffix="\n";

bool
RecursiveFibonnaciMethod::buildIL()
   {
   OMR::JitBuilder::IlBuilder *baseCase=NULL, *recursiveCase=NULL;
   IfThenElse(&baseCase, &recursiveCase,
      LessThan(
         Load("n"),
         ConstInt32(2)));

   DefineLocal("result", Int32);

   baseCase->Store("result",
   baseCase->   Load("n"));

   recursiveCase->Store("result",
   recursiveCase->   Add(
   recursiveCase->      Call("fib", 1,
   recursiveCase->         Sub(
   recursiveCase->            Load("n"),
   recursiveCase->            ConstInt32(1))),
   recursiveCase->      Call("fib", 1,
   recursiveCase->         Sub(
   recursiveCase->            Load("n"),
   recursiveCase->            ConstInt32(2)))));

#if defined(DEBUG_OUTPUT)
   Call("printString", 1,
      ConstInt64((int64_t)prefix));
   Call("printInt32", 1,
      Load("n"));
   Call("printString", 1,
      ConstInt64((int64_t)middle));
   Call("printInt32", 1,
      Load("result"));
   Call("printString", 1,
      ConstInt64((int64_t)suffix));
#endif

   Return(
      Load("result"));

   return true;
   }

int32_t 
RecursiveFibonnaciMethod::jit_compile_function(bool run_function, 
                     int32_t n, 
                     int32_t count) {
   bool initialized = initializeJit();
   if (!initialized)
      {
      fprintf(stderr, "FAIL: could not initialize JIT\n");
      exit(-1);
      }

   OMR::JitBuilder::TypeDictionary types;

   RecursiveFibonnaciMethod method(&types);
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
         RecursiveFibFunctionType *fib = (RecursiveFibFunctionType *)entry;
         result += fib(20);
      }
   }

   shutdownJit();

   return result;
}

int
RecursiveFibonnaciMethod::run(int n) {
   bool initialized = initializeJit();
   if (!initialized)
      {
      fprintf(stderr, "FAIL: could not initialize JIT\n");
      exit(-1);
      }

   OMR::JitBuilder::TypeDictionary types;

   RecursiveFibonnaciMethod method(&types);
   void *entry=0;
   int32_t rc = compileMethodBuilder(&method, &entry);
   if (rc != 0)
      {
      fprintf(stderr,"FAIL: compilation error %d\n", rc);
      exit(-2);
      }

   RecursiveFibFunctionType *fib = (RecursiveFibFunctionType *)entry;
   int32_t result = fib(20);

   shutdownJit();

   return result;
}

void
RecursiveFibonnaciMethod::testThroughput(std::ostream &ostream, 
                                         int32_t s_to_run, 
                                         int32_t ns_to_run) {
   
   int32_t ONE_BILLION=1000000000;

   struct timespec begin, current, elapsed;
   
   clock_gettime(CLOCK_MONOTONIC_RAW, &begin);

   elapsed.tv_sec = 0;
   elapsed.tv_nsec = 0;
  
   bool initialized = initializeJit();
   if (!initialized)
      {
      fprintf(stderr, "FAIL: could not initialize JIT\n");
      exit(-1);
      }

   OMR::JitBuilder::TypeDictionary types;

   RecursiveFibonnaciMethod method(&types);
   void *entry=0;
   int32_t rc = compileMethodBuilder(&method, &entry);
   if (rc != 0)
      {
      fprintf(stderr,"FAIL: compilation error %d\n", rc);
      exit(-2);
      }

   RecursiveFibFunctionType *fib = (RecursiveFibFunctionType *)entry;
   

   while(elapsed.tv_sec * ONE_BILLION + elapsed.tv_nsec < s_to_run * ONE_BILLION + ns_to_run) {
      int32_t result = fib(20);
      clock_gettime(CLOCK_MONOTONIC_RAW, &current);
      elapsed.tv_sec = current.tv_sec - begin.tv_sec;
      elapsed.tv_nsec = current.tv_nsec - begin.tv_nsec;
      ostream << elapsed.tv_sec * ONE_BILLION + elapsed.tv_nsec << std::endl;
   }

   shutdownJit();

}