CFLAGS=-I.

build:	main.cpp fib.cpp fib.h
	mkdir -p build
	g++ main.cpp fib.cpp -std=c++11 -O0 -o build/main.o

build-o3:	main.cpp fib.cpp fib.h
	mkdir -p build
	g++ main.cpp fib.cpp -std=c++11 -O3 -o build/main-o3.o


build-benchmark:	benchmark.cpp fib.cpp fib.h
	mkdir -p build
	g++ benchmark.cpp fib.cpp -std=c++11 -O0 -lbenchmark -lpthread -o build/benchmark.a

build-benchmark-o3:	benchmark.cpp fib.cpp fib.h
	mkdir -p build
	g++ benchmark.cpp fib.cpp -std=c++11 -O3 -lbenchmark -lpthread -o build/benchmark-o3.a

clean: 
	rm -rf build

run:
	./build/main.o

run-o3:
	./build/main-o3.o

run-benchmark:
	./build/benchmark.a --benchmark_report_aggregates_only --benchmark_repetitions=10

run-benchmark-o3:
	./build/benchmark-o3.a --benchmark_report_aggregates_only --benchmark_repetitions=10

