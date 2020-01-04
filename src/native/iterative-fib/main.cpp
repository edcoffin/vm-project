#include <stdio.h>
#include "fib.hpp"

int main() {
    int32_t result = 0;
    result = fib(0);
    printf("Result 0 = %d\n", result);
    result = fib(1);
    printf("Result 1 = %d\n", result);
    result = fib(2);
    printf("Result 2 = %d\n", result);
    result = fib(3);
    printf("Result 3 = %d\n", result);
    result = fib(4);
    printf("Result 4 = %d\n", result);
    result = fib(5);
    printf("Result 5 = %d\n", result);
}

