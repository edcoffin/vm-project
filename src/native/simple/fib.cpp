#include "fib.hpp"

int32_t fib(int32_t a){
     if(a < 2) {
         return a;
     }
     return fib(a - 1) + fib(a - 2);
}

int32_t fib_runner(int32_t a, int32_t count){
    int32_t result = 0;
    for(int i = 0; i < count; i++){
        result += fib(a);
    }
    return result;
}