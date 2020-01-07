#include <stdio.h>
#include "fib.hpp"

int main() {
    int32_t result = 0;
    result = fib_runner(20, 1);
    printf("Result = %d\n", result);
}

