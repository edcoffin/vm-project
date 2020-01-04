#include <stdio.h>
#include "simple.hpp"

#define DEBUG_OUTPUT

int main() {
    int32_t result = 0;
    result = simple(20);

    #if defined(DEBUG_OUTPUT)
    printf("Result=%d\n", result);
    #endif
}

