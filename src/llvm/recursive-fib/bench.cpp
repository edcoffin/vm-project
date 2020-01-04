#include <time.h>
#include <iostream>
#include "benchmark/benchmark.h"
#include "fib.hpp"

static void BM_Compile(benchmark::State& state) {
  for (auto _ : state) {
    jit_compile_function(false, 0, 0);
  }
}

static void BM_CompileRunOnce(benchmark::State& state) {
  for (auto _ : state) {
    jit_compile_function(true, 20, 1);
  }
}

static void BM_CompileRun1k(benchmark::State& state) {
  for (auto _ : state) {
    jit_compile_function(true, 20, 1000);
  }
}

BENCHMARK(BM_Compile);
BENCHMARK(BM_CompileRunOnce);
BENCHMARK(BM_CompileRun1k);

BENCHMARK_MAIN();