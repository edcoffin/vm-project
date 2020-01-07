#include "benchmark/benchmark.h"
#include "increment.hpp"

static void BM_Compile(benchmark::State& state) {
  int32_t result = 0;
  for (auto _ : state) {
    result = jit_compile_function(false, 0, 0);
  }
}

static void BM_CompileRunOnce(benchmark::State& state) {
  int32_t result = 0;
  for (auto _ : state) {
    result = jit_compile_function(true, 20, 1);
  }
}

static void BM_CompileRun100k(benchmark::State& state) {
  int32_t result = 0;
  for (auto _ : state) {
    result = jit_compile_function(true, 20, 100000);
  }
}

BENCHMARK(BM_Compile);
BENCHMARK(BM_CompileRunOnce);
BENCHMARK(BM_CompileRun100k);

BENCHMARK_MAIN();