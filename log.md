# Log
History, outstanding items and insights.

## 2019-12-18
    x - add readme
    - move benchmark to src/lib
    - move flamegraph to src/lib
    - update native/recursive-fib makefile to build with new benchmark locale (not system)
        - add benchmark target
        - add main target
    

## 2019-12-17
Goals:
    x Add Recursive Fib for ORM:
    
    x https://github.com/eclipse/omr/blob/master/jitbuilder/release/cpp/samples/RecursiveFib.cpp

Consider measurements:
    
    Memory: native vs jitBuilder
    CPU time: native vs jitbuilder
    Measure time spent compiling (extract from perf)

## 2019-12-16
+ Migrated work to Ubuntu

- Fibonacci program
    - recursive;
    - measure time;
    - native (no op vs optimized)
    - 40th fib
        + -O0 = 0.579880 seconds
        + -O3 = 0.501976 seconds
        + std dev
        + mean
        + average

    - google-bench <+discussion>
    + externalize the function; call with argument;
    + may need linux for testing properly
        + generated flamegraph!    

## 2019-12-12
- Write a simple C program
- Analyze performance
    - runtime time
    - considering measure throughput
    - memory
    - cache metrics

- Consider how to benchmark for report
    - iterations (throw away)
    - scripted
    - reproducible (from source)
    - how to measure and present

- The overhead of the framework
    - closest to the baseline (optimized C)
    - or better (SIMD in dotproduct)
    - analyze disassembly (gcc -S -masm=intel main.cpp)

## 2019-12-[10,11]
- Read up on linking + loading
- Looked into system performance

## 2019-12-09
- Setup structure
- Built OMR and ran jitBuilder tests
- Started to look at LLVM JIT; some more effort required here.
- Looked into benchmarking C++ code with the google benchmark framework.
