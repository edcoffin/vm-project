#include <stdio.h>
#include "fib.hpp"

int main() {
    int32_t result = 0;
    // bug in llvm-fib for 0 case; 19=6765 == fib(20)
    result = jit_compile_function(true, 19, 1);
    printf("Result = %d\n", result);
}

