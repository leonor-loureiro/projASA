CFLAGS = -Wall

all: graph run

run:
	./graph.o

graph:  graph.cpp
		g++ $(CFLAGS) graph.cpp -o graph.o

clean:
		rm graph.o