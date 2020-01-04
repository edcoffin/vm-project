#include "simple.hpp"
#include <stdio.h>
#define DEBUG_OUTPUT

int main() {
    int32_t result = SimpleMethod::run(20);
    #if defined(DEBUG_OUTPUT)
        printf("Result=%d\n", result);
    #endif
}