CFLAGS = -pedantic -O3 -ansi -Wall -lm

all: input

run:
	./main.o

input: graph.cpp graph.hpp main.cpp
	g++  $(CFLAGS) -o main.o main.cpp graph.cpp
proj:
	g++ -pedantic -O3 -ansi -Wall -lm proj1.cpp

clean:
	rm -f *.o *.out
