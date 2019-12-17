#include <stdio.h>
#include <time.h>
#include "fib.h"

int main() {
    struct timespec begin, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &begin);

    int32_t result = 0;
    result = fib(20);

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    printf ("Total time = %f seconds\n",
            (end.tv_nsec - begin.tv_nsec) / 1000000000.0 +
            (end.tv_sec  - begin.tv_sec));
}

