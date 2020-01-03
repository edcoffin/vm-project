#ifndef FIB_H_INCLUDED
#define FIB_H_INCLUDED

#include <cstdint>
#include <iostream>

int32_t fib(int a);

int32_t testThroughput(std::ostream&, int32_t, int32_t);

#endif
