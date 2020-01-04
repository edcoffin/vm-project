OUT			= ./build
MK_DIR		= mkdir -p $(OUT)

MAIN_OBJ		= main.o fib.o
BENCH_OBJ		= bench.o fib.o
TPP_OBJ			= tp.o fib.o
1KTIME_OBJ		= 1ktime.o fib.o

CXXFLAGS	+= -O0 
HEADERS		= -I. -I../../lib/benchmark/include
LDFLAGS		+= -L../../lib/benchmark/build/src
LDLIBS		+= -lbenchmark -lpthread
LLVM_CONFIG = ../../lib/llvm-project/build/bin/llvm-config

main: $(MAIN_OBJ)
	$(MK_DIR)
	$(CXX) $(CXXFLAGS) -o $(OUT)/$@ $(MAIN_OBJ) $(HEADERS) `$(LLVM_CONFIG) --cppflags --ldflags --system-libs --libs core executionengine interpreter mc mcjit support nativecodegen`

bench: $(BENCH_OBJ)
	$(MK_DIR)
	$(CXX) $(CXXFLAGS) -o $(OUT)/$@ $(BENCH_OBJ) $(HEADERS) $(LDFLAGS) $(LDLIBS) `$(LLVM_CONFIG) --cppflags --ldflags --system-libs --libs core executionengine interpreter mc mcjit support nativecodegen`

tp: $(TPP_OBJ)
	$(MK_DIR)
	$(CXX) $(CXXFLAGS) -o $(OUT)/$@ $(TPP_OBJ) $(HEADERS) `$(LLVM_CONFIG) --cppflags --ldflags --system-libs --libs core executionengine interpreter mc mcjit support nativecodegen`

1ktime: $(1KTIME_OBJ) 
	$(MK_DIR)
	$(CXX) $(CXXFLAGS) -o $(OUT)/$@ $(1KTIME_OBJ) $(HEADERS) `$(LLVM_CONFIG) --cppflags --ldflags --system-libs --libs core executionengine interpreter mc mcjit support nativecodegen`

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o $(HEADERS)

bench.o: bench.cpp
	$(CXX) $(CXXFLAGS) -c bench.cpp -o bench.o $(HEADERS) 

fib.o: fib.cpp
	$(CXX) $(CXXFLAGS) -c fib.cpp -o $@ `$(LLVM_CONFIG) --cppflags` $(HEADERS)

tp.o: tp.cpp
	$(CXX) $(CXXFLAGS) $(HEADERS) -c $< -o $@	

1ktime.o: 1ktime.cpp
	$(CXX) $(CXXFLAGS) $(HEADERS) -c $< -o $@	

clean:
	rm fib.o bench.o main.o tp.o
	rm -rf $(OUT)

run-bench:
	$(OUT)/bench --benchmark_report_aggregates_only --benchmark_repetitions=10

run-tp: tp
	$(MK_DIR)
	mkdir -p $(OUT)/tp_results
	python tp_runner.py $(OUT)/tp