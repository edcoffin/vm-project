#include <time.h>
#include <iostream>
#include "benchmark/benchmark.h"
#include "fib.hpp"

static void BM_RunOnce(benchmark::State& state) {
  int32_t result = 0;
  for (auto _ : state) {
    result = fib_runner(20, 1);
  }
}

static void BM_Run1k(benchmark::State& state) {
  int32_t result = 0;
  for (auto _ : state) {
    result = fib_runner(20, 1000);
  }
}

BENCHMARK(BM_RunOnce);
BENCHMARK(BM_Run1k);

BENCHMARK_MAIN();