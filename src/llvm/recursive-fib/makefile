OUT			= ./build
MK_DIR		= mkdir -p $(OUT)

MAIN_OBJ		= main.o fib.o
BENCH_OBJ		= bench.o fib.o
TPP_OBJ			= tpp.o fib.o

CXXFLAGS	+= -std=c++11 -O3 
HEADERS		= -I. -I../../lib/benchmark/include
LDFLAGS		+= -L../../lib/benchmark/build/src
LDLIBS		+= -lbenchmark -lpthread
LLVM_CONFIG = ../../lib/llvm-project/build/bin/llvm-config

main: $(MAIN_OBJ)
	$(MK_DIR)
	$(CXX) -o $(OUT)/$@ $(MAIN_OBJ) $(HEADERS) `$(LLVM_CONFIG) --cppflags --ldflags --system-libs --libs core executionengine interpreter mc mcjit support nativecodegen`

bench: $(BENCH_OBJ)
	$(MK_DIR)
	$(CXX) -o $(OUT)/$@ $(BENCH_OBJ) $(HEADERS) $(LDFLAGS) $(LDLIBS) `$(LLVM_CONFIG) --cppflags --ldflags --system-libs --libs core executionengine interpreter mc mcjit support nativecodegen`

tpp: $(TPP_OBJ)
	$(MK_DIR)
	$(CXX) -o $(OUT)/$@ $(TPP_OBJ) $(HEADERS) `$(LLVM_CONFIG) --cppflags --ldflags --system-libs --libs core executionengine interpreter mc mcjit support nativecodegen`

main.o: main.cpp
	$(CXX) -c main.cpp -o main.o $(HEADERS)

bench.o: bench.cpp
	$(CXX) -c bench.cpp -o bench.o $(HEADERS) 

fib.o: fib.cpp
	$(CXX) -c fib.cpp -o $@ `$(LLVM_CONFIG) --cppflags` $(HEADERS)

tp.o: tp.cpp
	$(CXX) $(CXXFLAGS) $(HEADERS) -c $< -o $@	

clean:
	rm fib.o bench.o main.o tp.o
	rm -rf $(OUT)

run-bench:
	$(OUT)/bench --benchmark_report_aggregates_only --benchmark_repetitions=10

	# g++ -g -O3 main.cpp `llvm-config --cppflags --ldflags --system-libs --libs core executionengine interpreter mc mcjit support nativecodegen` -o main