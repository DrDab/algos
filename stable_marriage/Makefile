CXX = g++
CXXFLAGS = -Wall -g -std=c++17

all: gs

gs: gs.o
	$(CXX) $(CXXFLAGS) gs.o -o gs

gs.o: gs.cc
	$(CXX) $(CXXFLAGS) -c gs.cc

clean:
	rm -rf gs *.o *~


