OUT			= ./build
MK_DIR		= mkdir -p $(OUT)

MAIN_OBJ		= main.o increment.o
BENCH_OBJ		= bench.o increment.o

CXX 		= g++
CXXFLAGS	+= -O3 -std=c++14

HEADERS		= -I. -I../../lib/benchmark/include
LDFLAGS		+= -L../../lib/benchmark/build/src
LDLIBS		+= -lbenchmark -lpthread
LLVM_CONFIG = ../../lib/llvm-project/build/bin/llvm-config
LLVM_COMPONENTS = core executionengine interpreter passes mc mcjit support nativecodegen

main: $(MAIN_OBJ)
	$(MK_DIR)
	$(CXX) $(CXXFLAGS) -o $(OUT)/$@ $(MAIN_OBJ) $(HEADERS) `$(LLVM_CONFIG) --cppflags --ldflags --system-libs --libs $(LLVM_COMPONENTS)`

bench: $(BENCH_OBJ)
	$(MK_DIR)
	$(CXX) $(CXXFLAGS) -o $(OUT)/$@ $(BENCH_OBJ) $(HEADERS) $(LDFLAGS) $(LDLIBS) `$(LLVM_CONFIG) --cppflags --ldflags --system-libs --libs $(LLVM_COMPONENTS)`

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o $(HEADERS)

bench.o: bench.cpp
	$(CXX) $(CXXFLAGS) -c bench.cpp -o bench.o $(HEADERS) 

increment.o: increment.cpp
	$(CXX) $(CXXFLAGS) -c increment.cpp -o $@ `$(LLVM_CONFIG) --cppflags` $(HEADERS)

clean:
	rm increment.o bench.o main.o
	rm -rf $(OUT)

run-bench: bench
	$(OUT)/bench --benchmark_report_aggregates_only --benchmark_repetitions=25
