OUT			= ./build
SRC			= fib.cpp
OBJ			= $(patsubst %.cpp,%.o, $(SRC))
MK_DIR		= mkdir -p $(OUT)

CXXFLAGS	+= -std=c++11 -O3 
HEADERS		= -I. -I ../../lib/benchmark/include
LDFLAGS		+= -L../../lib/benchmark/build/src
LDLIBS		+= -lbenchmark -lpthread

main: $(OBJ)
	$(MK_DIR)
	$(CXX) $(HEADERS) -o $(OUT)/$@ $@.cpp $(OBJ)

bench: $(OBJ)
	$(MK_DIR)
	$(CXX) $(HEADERS) -o $(OUT)/$@ $@.cpp $(OBJ) $(LDFLAGS) $(LDLIBS)

clean:
	rm $(OBJ)
	rm -rf $(OUT)

run-bench:
	$(OUT)/bench --benchmark_report_aggregates_only --benchmark_repetitions=10