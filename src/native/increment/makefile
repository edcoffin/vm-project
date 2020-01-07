OUT			= ./build
MK_DIR		= mkdir -p $(OUT)

MAIN_OBJ		= main.o increment.o
BENCH_OBJ		= bench.o increment.o

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

increment.o: increment.cpp
	$(CXX) $(CXXFLAGS) -c increment.cpp -o increment.o $(HEADERS)

clean:
	rm increment.o main.o bench.o
	rm -rf $(OUT)

run-bench: bench
	$(OUT)/bench --benchmark_report_aggregates_only --benchmark_repetitions=20