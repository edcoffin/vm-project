#include <stdio.h>
#include "increment.hpp"

#define DEBUG_OUTPUT

int main() {
    int32_t result = 0;
    result = increment_runner(20, 1);
    #if defined(DEBUG_OUTPUT)
    printf("Result=%d\n", result);
    #endif
}

