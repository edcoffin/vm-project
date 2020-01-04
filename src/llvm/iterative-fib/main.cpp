#include <stdio.h>
#include "fib.hpp"

int main() {
    int32_t result = 0;
    // bug in llvm-fib for 0 case; 19=6765 == fib(20)
    result = fib(19);
    printf("Result = %d\n", result);
}

