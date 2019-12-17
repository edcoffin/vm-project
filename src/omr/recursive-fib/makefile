LIBJITBUILDERDIR=../../lib/omr/jitbuilder/release/cpp
LIBJITBUILDER=$(LIBJITBUILDERDIR)/libjitbuilder.a

CXX = g++
CXXFLAGS = -g -c -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -O0 -std=c++0x -fno-rtti -fPIC  -I$(LIBJITBUILDERDIR)/include -I../../lib/omr/include_core -Wno-write-strings

recfib : $(LIBJITBUILDER) RecursiveFib.o
	mkdir -p ./build
	$(CXX) -g -fno-rtti -o ./build/$@ ./build/RecursiveFib.o -L$(LIBJITBUILDERDIR) -ljitbuilder -ldl

RecursiveFib.o: RecursiveFib.cpp RecursiveFib.hpp
	mkdir -p ./build
	$(CXX) -o ./build/$@ $(CXXFLAGS) $<

clean:
	rm -rf ./build