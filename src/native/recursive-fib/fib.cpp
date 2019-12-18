#include "fib.hpp"

int32_t fib(int32_t a){
     if(0 == a) {
         return 0;
     }
     if(1 == a){
         return 1;
     }
     return fib(a - 1) + fib(a - 2);
}