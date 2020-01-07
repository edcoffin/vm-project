#include <time.h>
#include <iostream>
#include "benchmark/benchmark.h"
#include "increment.hpp"

static void BM_RunOnce(benchmark::State& state) {
  int32_t result = 0;
  for (auto _ : state) {
    result = increment_runner(20, 1);
  }
}

static void BM_Run100k(benchmark::State& state) {
  int32_t result = 0;
  for (auto _ : state) {
    result += increment_runner(20, 100000);
  }
}

BENCHMARK(BM_RunOnce);
BENCHMARK(BM_Run100k);

BENCHMARK_MAIN();