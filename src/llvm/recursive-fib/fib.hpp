#ifndef FIB_H_INCLUDED
#define FIB_H_INCLUDED

#include <cstdint>
#include <iostream>

int32_t jit_compile_function(bool run_function, int32_t n, int32_t count);
int32_t testThroughput(std::ostream&, int32_t, int32_t n);

#endif
