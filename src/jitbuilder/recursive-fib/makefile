OUT			= ./build
MK_DIR		= mkdir -p $(OUT)

BENCH_DIR 	= ../../lib/benchmark
JITBUILDER_DIR = ../../lib/omr/jitbuilder/release/cpp

CXX      = /usr/bin/g++
CXXFLAGS	= --std=c++0x -fno-rtti -fPIC -Wno-write-strings -O3
HEADERS		= -I. -I$(BENCH_DIR)/include -I../../lib/omr/include_core -I$(JITBUILDER_DIR)/include

BENCH_LD	= -L$(BENCH_DIR)/build/src -lbenchmark -lpthread
JITBUILDER_LD	= -L$(JITBUILDER_DIR) -ljitbuilder -ldl 

main: fib.o main.o
	$(MK_DIR)
	$(CXX) $(CXXFLAGS) -o $(OUT)/$@ fib.o main.o $(JITBUILDER_LD)

bench: fib.o bench.o
	$(MK_DIR)
	$(CXX) $(CXXFLAGS) -o $(OUT)/$@ fib.o bench.o $(JITBUILDER_LD) $(BENCH_LD)


fib.o: fib.cpp
	$(CXX) $(CXXFLAGS) $(HEADERS) -c $< -o $@

main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(HEADERS) -c $< -o $@

bench.o: bench.cpp
	$(CXX) $(CXXFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm fib.o bench.o main.o
	rm -rf $(OUT)

run-bench: bench
	$(OUT)/bench --benchmark_report_aggregates_only --benchmark_repetitions=20
