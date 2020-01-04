#include <stdio.h>
#include "fib.hpp"

int main() {
    int32_t result = 0;    
    result = jit_compile_function(true, 20, 1);
    printf("Result=%d\n", result);
}

