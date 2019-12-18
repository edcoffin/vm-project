# A Comparison of JIT Compiler Overhead during Run-time

## Building project
The project has the following dependencies:
- gcc or clang
- cmake 3.2+
- Linux (2.6.31+) with `perf` installed (perf_events available)
- [google benchmark](https://github.com/google/benchmark)
- [Eclipse OMR](https://github.com/eclipse/omr/tree/master/jitbuilder/release)
- LLVM
- libjit

After cloning this repository `cd` into `src/lib` and perform the following operations.

### Install and Build Google Benchmark
Benchmark is a microbenchmark support library. We use it to measure the CPU time spent executing each program.

Clone the Benchmark repository in `src/lib`
```
# Check out the library.
$ git clone https://github.com/google/benchmark.git
# Benchmark requires Google Test as a dependency. Add the source tree as a subdirectory.
$ git clone https://github.com/google/googletest.git benchmark/googletest
# Go to the library root directory
$ cd benchmark
# Make a build directory to place the build output.
$ mkdir build && cd build
# Generate a Makefile with cmake.
# Use cmake -G <generator> to generate a different file type.
$ cmake -DCMAKE_BUILD_TYPE=Release ../
# Build the library.
# Use make -j<number_of_parallel_jobs> to speed up the build process, e.g. make -j8 .
$ make 
```
### Install and Build JITBuilder
Clone the Eclipse OMR repository in `src/lib`:
`$ git clone https://github.com/eclipse/omr`

```
$ cd omr
$ mkdir build
$ cd build
$ cmake .. -DOMR_COMPILER=1 -DOMR_JITBUILDER=1 -DOMR_TEST_COMPILER=1
$ make
$ cd ../jitbuilder/release/cpp
$ ln -s ../../../build/jitbuilder/libjitbuilder.a .
# build and run the code samples
$ make test
```

The code used in this project will reference the code referenced in `src/lib/omr`.




