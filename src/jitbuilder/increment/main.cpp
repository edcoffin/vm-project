#include "increment.hpp"
#include <stdio.h>
#define DEBUG_OUTPUT

int main() {
    int32_t result = IncrementMethod::jit_compile_function(true, 20, 1);
    #if defined(DEBUG_OUTPUT)
        printf("Result=%d\n", result);
    #endif
}