#ifndef _GRAPH_H_
#define  _GRAPH_H_

#include <list>
#include <queue>
using namespace  std;


class Edge{
	public:
    	int predecessor;
    	int successor;

        Edge(int pre, int suc); //Constructor
};


class Graph{
	private:
		int V;           // number of vertices
		list<int> *adj;  // array of adjacency lists
		int *indegree;   // array with the indegree of each vertex
	public:

		/* Constructor */
		Graph(int v);

		/* Add an edge from vertice v to vertice w */
		void insertEdge(Edge e);

		/* Prints the topological order of the graph's vertices */
		vector<int> topologicalSort();
};

#endif
