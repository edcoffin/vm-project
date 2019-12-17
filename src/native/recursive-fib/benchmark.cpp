#include <time.h>
#include <iostream>
#include <benchmark/benchmark.h>
#include "fib.h"

static void BM_Fib(benchmark::State& state) {
  int32_t result = 0;
  for (auto _ : state) {
    result += fib(20);
  }
}
BENCHMARK(BM_Fib);

BENCHMARK_MAIN();