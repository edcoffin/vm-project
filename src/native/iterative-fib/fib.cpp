#include "fib.hpp"

int32_t fib(int32_t n) {
    
    if(n == 0) {
        return 0;
    }
    
    int lastSum = 0;
    int sum = 1;
    
    for(int i = 1; i < n; i++) {
       int tempSum = sum + lastSum;
       lastSum = sum;
       sum = tempSum;
    }
    return sum;
}

int32_t fib_runner(int32_t n, int32_t count){
    int32_t result = 0;
    for(int i = 0; i < count; i++){
        result += fib(n);
    }
    return result;
}