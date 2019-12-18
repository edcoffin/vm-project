#include <stdio.h>
#include "fib.hpp"

#define DEBUG_OUTPUT

int main() {
    int32_t result = 0;
    result = fib(20);

    #if defined(DEBUG_OUTPUT)
    printf("Result=%d\n", result);
    #endif
}

