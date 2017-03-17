CFLAGS = -pedantic -O3 -ansi -Wall -lm

all: input

run:
	./inputProcess.o

input: graph.cpp graph.hpp inputProcess.cpp
	g++  $(CFLAGS) -o inputProcess.o inputProcess.cpp graph.cpp
