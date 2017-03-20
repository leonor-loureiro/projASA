#include <iostream>
#include <list>
#include <queue>
using namespace  std;

/*************************
 *    ASA - LEIC-TP      *
 * 		Grupo 32		 *
 * Andre Fonseca 84698	 *
 * Leonor Loureiro 84736 *
 *************************/


/**
 * Class representation of an Edge
 * An Edge or Arc is a connection between 2 vertices.
 */
class Edge{
	public:
    	int predecessor;	//vertex from which edge originates from
    	int successor;		// vertex to which the edge is going to

		/**
		 * Default consctructor
		 * @param pre the predecessor of the edge
		 * @param suc the successor of the edge
		 */
        Edge(int pre, int suc);
};


/**
 * Structure used to model relations between 2 pairs
 * This implementation of a directional graph is made through an adjacency list
 */
class Graph{
	private:
		int nrOfVertices;           // number of vertices
		list<int> *adjacencyLists;  // array of adjancy lists
		int *indegree;   			// array with the indegree of each vertex
	public:

		/**
		 * Default Constructor
		 * @param v the size(number of vertecis) of the graph
		 */
		Graph(int v);

		/**
		 * Inserts and edge to the graph
		 * @param e Edge to be added to the graph
		 */
		void insertEdge(Edge e);

		/**
		 * Based on Kahn’s algorithm for Topological Sorting graphs
		 * Prints "Incoerente" if there's a loop in graphs
		 * Prints "Insuficiente" if there's more than 1 possible topological sort
		 * and no loops were found in graph.
		 * returns the Vector with the vertices ordered topologically
		 */
		vector<int> topologicalSort();
};



/**
 * Receives input  from user in pairs of integers, first pair has the number of
 * photos and the number of relations that are gonna be given between the photos
 * the next pairs are the relations, where the first photo occured before the second.
 * prints, if possible, the sorted order of the photos.
 */
int main(int argc, char const *argv[]) {

    int nrOfPhotos;
    int nrOfPairs;
    int photo1;
    int photo2;
    int i;

    std::cin >> nrOfPhotos >> nrOfPairs;
    Graph graph(nrOfPhotos);

/* ignored to improved performance
    if (nrOfPhotos < 2){
		std::cout << "Bad input error. Number of photos:"<< nrOfPhotos << "\nExiting program..." << '\n';
        return 0;
    }
*/

    while(nrOfPairs > 0){
        std::cin >> photo1 >> photo2; // photo1 occured before photo2

/* ignore to improve performance
		if(photo1 < 1 || photo2 < 1 || photo1 - 1 > nrOfPhotos || photo2 -1 > nrOfPhotos){
            std::cout << "Bad input Error.\nExiting program..." << '\n';
			return 0;
        }
*/
        graph.insertEdge(Edge(photo1 - 1, photo2 - 1)); //compensation for input starting on 1 and not 0
        nrOfPairs--;
    }

    std::vector <int> order = graph.topologicalSort();

    if (order.size() == 0)
        return 0;

	/* prints ordered vector */
    for( i = 0; i < nrOfPhotos-1; i++)
		cout << order[i]+1 << " " ;
	cout << order[i]+1 <<'\n';

    return 0;
}






Edge::Edge(int pre, int suc){
	predecessor = pre;
	successor = suc;
}


Graph::Graph(int v){
	nrOfVertices = v;
	adjacencyLists = new list<int>[v];
	indegree = new int[v];
	for(int i = 0; i < v; i++)
		indegree[i] = 0;
}

void Graph::insertEdge(Edge e){
	adjacencyLists[e.predecessor].push_back(e.successor);
	indegree[e.successor]++;
}


vector<int> Graph::topologicalSort(){

	vector<int> order; 			//Topologically Ordered vector
	queue<int> sourceVertices; 	// Stores vertices with 0 indegree
	bool insufficient = false;	// status flag for insufficiente error found
	int visitedVertices = 0;	// counter of visited vertices

	/* adds all the vertices with 0 indegree to the sourceVertices*/
	for(int i = 0; i < nrOfVertices; i++){
		if(indegree[i] == 0){
			if (!sourceVertices.empty())
				insufficient = true;
			sourceVertices.push(i);
		}
	}

	while(!sourceVertices.empty()){

		/* Removes the first element with 0 indegree and adds to ordered vector*/
		int vertex = sourceVertices.front();
		sourceVertices.pop();
		order.push_back(vertex);
		visitedVertices++;

		/* Decreses the indegrees of the vertices adjacent to the current vertex,
		 * if one of them reaches 0 indegree, adds it to sourceVertices */
		for(list<int>::iterator i = adjacencyLists[vertex].begin(); i!=adjacencyLists[vertex].end(); i++){
			if(--indegree[*i] == 0){
				if(!sourceVertices.empty())
					insufficient = true;
				sourceVertices.push(*i);
			}
		}
	}

	/* Checks for the existance of loops */
	if(visitedVertices != nrOfVertices){
		cout << "Incoerente" << '\n';
		return vector<int> ();
	}

	/* Checks for case in which there's more than one topological order which
	generates insufficient error*/
	if(insufficient){
		cout << "Insuficiente" << '\n';
		return vector<int> ();
	}

	return order;
}
