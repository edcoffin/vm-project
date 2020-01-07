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

static void BM_CompileRun10k(benchmark::State& state) {
  int32_t result = 0;
  for (auto _ : state) {
    result = jit_compile_function(true, 20, 10000);
  }
}

BENCHMARK(BM_Compile);
BENCHMARK(BM_CompileRunOnce);
BENCHMARK(BM_CompileRun10k);

BENCHMARK_MAIN();