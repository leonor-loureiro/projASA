#include <iostream>
#include "graph.hpp"

int main(int argc, char const *argv[]) {

    int nrOfPhotos;
    int nrOfPairs;
    int photo1;
    int photo2;

    std::cin >> nrOfPhotos >> nrOfPairs;

    Graph graph(nrOfPhotos);

    if (nrOfPhotos < 2){
        // Tratar de erro
    }


    while(nrOfPairs > 0){
        std::cin >> photo1 >> photo2;
        // photo1 occured before photo2

        if(photo1 < 1 || photo2 < 1 || photo1 > nrOfPhotos || photo2 > nrOfPhotos){
            // Tratar do erro
        }

        graph.insertEdge(Edge(photo1 - 1, photo2 - 1));

        nrOfPairs--;
    }

    std::vector <int> order = graph.topologicalSort();

    if (order.size() == 0)
        return 0;

    for(int i = 0; i < nrOfPhotos; i++){
		cout << order[i]+1 << " " ;
	}
	cout << std::endl;


    return 0;
}
