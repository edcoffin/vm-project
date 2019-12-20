# Log
History, outstanding items and insights.

## 2019-12-20
### Next steps

- What will benefit the group during a seminar
    - focus on work
- Benchmarking tools (future seminar topic)
- Experiments and Results
    - Can we benchmark JIT
    - Execution Time by function (flamegraphs)
    - Memory (RSS, WSS) over time
- We need an application to run for a long time… to see the long term benefits (dominated by JIT compilation)
    - Can we measure throughput? (visualize time spent with JIT)
    - Can we compare to native O3 results...
        - More interesting than a recursive-fib?
    - Relative ns + result (buckets of 1000 ns) 
- What JIT optimizations can we apply to the compilers?
    - TRJIT: noOpt? Scorching? Disable profiling? Not considering a staged compilation scenario?
    - Does jitBuilder automatically increment optimizations?
- In addition to rec-fib --- what is another common application we can write.
- What is interesting about rec-fib? 
- Compare generated JIT assembler (log it?)

## 2019-12-19
    - built omr example on mac
    - added llvm fib example
    - ran /usr/bin/time -v ./build/main maxrss (9936 OMR vs 32396 for LLVM)
        - note version; compare to ORC?
    - compare size where asserts are off?
    - massif ? for valgrind

## 2019-12-18
    x - add readme
    x - move benchmark to src/lib
    
    x - update native/recursive-fib makefile to build with new benchmark locale (not system)
        - add benchmark target
        - add main target
    
    x - update omr/recursive-fib
        - add main target
        - get building! manual if need be.
        - add benchmark target
      

    x - move flamegraph to src/lib
        ? what am I scripting with flamegraph;
    


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
