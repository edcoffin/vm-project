# Log
History, outstanding items and insights.

## 2020-01-08
- rss results ? page faults
- usability
- note the CPU and running application with desktop
- quality of the generated code
- remove note on flamegraphs
- related work
    - benchmarking JIT? is there a paper
    - paper on interoperability of LLVM and JitBuilder
- future work
    - more configuration for JitBuilder
    - Investigate ORC
    - effects on Code Cache
    - ?
- Summary

...

- Poster
- Get LLVM built with debug symbols, investigate perf. ? what does this tell me.
 - total time spent in framework, vs total time spent doing work.


## 2020-01-07
x- update note on N runs in reports
x- update to 1k runs
x- update to 03
x- update to 20 reps

x- store in bench-results

x- increment
	x - llvm
	x - jitbuilder	
	x - native
x- rfib
	x - llvm
	x - jitbuilder	
	x - native
x- ifib
	x - llvm
	x - jitbuilder	
	x - native

- measure linked files!



## 2020-01-02
x - add report template and begin writing
- design throughput experiment 
    - tp.cpp
        - write to tp_results/001
    - tp_runner.py
    - tp_stats.py

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
