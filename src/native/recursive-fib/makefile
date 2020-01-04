OUT			= ./build
MK_DIR		= mkdir -p $(OUT)

MAIN_OBJ		= main.o fib.o
BENCH_OBJ		= bench.o fib.o

CXXFLAGS	+= -std=c++11 -O3
HEADERS		= -I. -I../../lib/benchmark/include
LDFLAGS		+= -L../../lib/benchmark/build/src
LDLIBS		+= -lbenchmark -lpthread

main: $(MAIN_OBJ)
	$(MK_DIR)
	$(CXX) $(CXXFLAGS) -o $(OUT)/$@ $(MAIN_OBJ) $(HEADERS)

bench: $(BENCH_OBJ)
	$(MK_DIR)
	$(CXX) $(CXXFLAGS) -o $(OUT)/$@ $(BENCH_OBJ) $(HEADERS) $(LDFLAGS) $(LDLIBS)

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o $(HEADERS)

bench.o: bench.cpp
	$(CXX) $(CXXFLAGS) -c bench.cpp -o bench.o $(HEADERS) 

fib.o: fib.cpp
	$(CXX) $(CXXFLAGS) -c fib.cpp -o fib.o $(HEADERS)

clean:
	rm fib.o bench.o main.o
	rm -rf $(OUT)

run-bench:
	$(OUT)/bench --benchmark_report_aggregates_only --benchmark_repetitions=10