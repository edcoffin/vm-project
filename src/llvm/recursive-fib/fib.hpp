#ifndef FIB_H_INCLUDED
#define FIB_H_INCLUDED

#include <cstdint>

int32_t fib(int a);

void testThroughput(std::ostream&, int32_t, int32_t);

#endif
