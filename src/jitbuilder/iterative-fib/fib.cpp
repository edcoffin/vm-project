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

IterativeFibonnaciMethod::IterativeFibonnaciMethod(OMR::JitBuilder::TypeDictionary *types)
   : OMR::JitBuilder::MethodBuilder(types)
   {
   DefineLine(LINETOSTR(__LINE__));
   DefineFile(__FILE__);

   DefineName("fib_iter"); // defines _method
   DefineParameter("n", Int32);
   DefineReturnType(Int32);
   }

static const char *prefix="fib(";
static const char *middle=") = ";
static const char *suffix="\n";

bool
IterativeFibonnaciMethod::buildIL()
   {
   OMR::JitBuilder::IlBuilder *returnN = NULL;
   IfThen(&returnN,
      LessThan(
         Load("n"),
         ConstInt32(2)));

   returnN->Return(
   returnN->   Load("n"));

   Store("LastSum",
      ConstInt32(0));

   Store("Sum",
      ConstInt32(1));

   IlBuilder *iloop = NULL;
   ForLoopUp("i", &iloop,
           ConstInt32(1),
           Load("n"),
           ConstInt32(1));

   iloop->Store("tempSum",
   iloop->   Add(
   iloop->      Load("Sum"),
   iloop->      Load("LastSum")));
   iloop->Store("LastSum",
   iloop->   Load("Sum"));
   iloop->Store("Sum",
   iloop->   Load("tempSum"));

   Return(
      Load("Sum"));

   return true;
   }

int32_t 
IterativeFibonnaciMethod::jit_compile_function(bool run_function, 
                     int32_t n, 
                     int32_t count) {
   bool initialized = initializeJit();
   if (!initialized)
      {
      fprintf(stderr, "FAIL: could not initialize JIT\n");
      exit(-1);
      }

   OMR::JitBuilder::TypeDictionary types;

   IterativeFibonnaciMethod method(&types);
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
         IterativeFibFunctionType *fib = (IterativeFibFunctionType *)entry;
         result += fib(20);
      }
   }

   shutdownJit();

   return result;
}

int
IterativeFibonnaciMethod::run(int n) {
   bool initialized = initializeJit();
   if (!initialized)
      {
      fprintf(stderr, "FAIL: could not initialize JIT\n");
      exit(-1);
      }

   OMR::JitBuilder::TypeDictionary types;

   IterativeFibonnaciMethod method(&types);
   void *entry=0;
   int32_t rc = compileMethodBuilder(&method, &entry);
   if (rc != 0)
      {
      fprintf(stderr,"FAIL: compilation error %d\n", rc);
      exit(-2);
      }

   IterativeFibFunctionType *fib = (IterativeFibFunctionType *)entry;
   int32_t result = fib(20);

   shutdownJit();

   return result;
}

void
IterativeFibonnaciMethod::testThroughput(std::ostream &ostream, 
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

   IterativeFibonnaciMethod method(&types);
   void *entry=0;
   int32_t rc = compileMethodBuilder(&method, &entry);
   if (rc != 0)
      {
      fprintf(stderr,"FAIL: compilation error %d\n", rc);
      exit(-2);
      }

   IterativeFibFunctionType *fib = (IterativeFibFunctionType *)entry;
   

   while(elapsed.tv_sec * ONE_BILLION + elapsed.tv_nsec < s_to_run * ONE_BILLION + ns_to_run) {
      int32_t result = fib(20);
      clock_gettime(CLOCK_MONOTONIC_RAW, &current);
      elapsed.tv_sec = current.tv_sec - begin.tv_sec;
      elapsed.tv_nsec = current.tv_nsec - begin.tv_nsec;
      ostream << elapsed.tv_sec * ONE_BILLION + elapsed.tv_nsec << std::endl;
   }

   shutdownJit();

}