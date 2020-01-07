#include <stdio.h>
#include "fib.hpp"

#define DEBUG_OUTPUT

int main() {
    int32_t result = 0;
    result = fib_runner(20, 1);

    #if defined(DEBUG_OUTPUT)
    printf("Result=%d\n", result);
    #endif
}

