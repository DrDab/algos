CXX = g++
CXXFLAGS = -Wall -g -std=c++17

all: gs

ex7: ex7.o
	$(CXX) $(CXXFLAGS) gs.o -o gs

ex7.o: ex7.cc Vector.h
	$(CXX) $(CXXFLAGS) -c gs.cc

clean:
	rm -rf gs *.o *~


