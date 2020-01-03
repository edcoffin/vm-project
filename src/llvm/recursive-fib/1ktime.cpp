#include <stdio.h>
#include <time.h>

#include "fib.hpp"


int main() {
    struct timespec begin, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &begin);

    int32_t result = 0;
    
    for(int i = 0; i < 1000; i++) {
        result += fib(20);
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    printf("%ld", (int64_t)(( end.tv_sec - begin.tv_sec ) * 1000000000  + 
    end.tv_nsec - begin.tv_nsec));
}

