all: fraction_demo

CXX		= g++
CXXFLAGS 	= -O3 -march=native -Wall

fraction_demo: fraction_demo.cpp fraction.o
	$(CXX)	$(CXXFLAGS) -o $@ $^

fraction.o: 	fraction.cpp fraction.hh
	$(CXX) 	$(CXXFLAGS) -c -o $@ $<

clean:
	rm *.o
