#include <iostream>
#include <list>
#include <queue>
using namespace  std;

class Graph{
	private:
		int V;           // numeber of vertices
		list<int> *adj;  // array of adjacency lists
		int *indegree;   // array with the indegree of each vertice
	public:

		/* Constructor */
		Graph(int v);

		/* Add an edge from vertice v to vertice w */
		void InsertE(int v, int w);

		/* Prints the topological order of the graph's vertices */
		void TopologicalSort();

};

Graph::Graph(int v){
	V = v;
	adj = new list<int>[v];
	indegree = new int[v];
	for(int i = 0; i < v; i++)
		indegree[i]=0;
}

void Graph::InsertE(int w, int v){
	adj[w].push_back(v); 
	indegree[v]++;
}


void Graph::TopologicalSort(){
	
	/* Cria um vetor para registar o resultado da ordenacao */
	vector<int> order;

	/* Armazena o vertice sem arcos de entrada */
	queue<int> queue;

	/* Flag para insufficient*/
	bool insufficient = false;

	/* Adiciona a lista de espera todos os verices sem arcos
	 * de entrada */		
	for(int i = 0; i < V; i++)
		if(indegree[i] == 0){
			if (!queue.empty()){
				insufficient = true;
			}
			queue.push(i);
		}
			

	int cnt_visit = 1;     // Indica o numero de vertices visitados

	/* Retira, um a um os vertices da fila de espera e adiciona
	 * os vertices adjacente quando o seu in degree atinge o zero */
	while(!queue.empty()){

		/* Remove o primeiro vertice da fila de espera e adiciona-o
		 * a ordem topologica */
		int x = queue.front();
		queue.pop();
		order.push_back(x);
	
		/*Itera os todos vertices adjacentes ao vertice x e
		 * decrementa o seu indegree numa unidade */
		for(list<int>::iterator i = adj[x].begin(); i!=adj[x].end(); i++){
			if(--indegree[*i] == 0){
				if(!queue.empty()){
					insufficient = true;
				}
				queue.push(*i);
			}
			cnt_visit++;
		}
		
	}

	
	/* Verifica se o grafo nao tem uma unica ordenacao possivel */
	if(insufficient){
		cout << "Insuficiente" << endl;
		return;
	}

	/* Verifica se encontrou um ciclo */
	if(cnt_visit!=V){
		cout << "Incoerente" << endl;
		return;
	}

	/*Imprimir a ordem topologica */
	for(int i = 0; i < V; i++){
		cout << order[i] << " " ;
	}
	cout << endl;

}

int main(int argc, char const *argv[])
{
	Graph g(4);
    g.InsertE(0, 1);
    g.InsertE(1, 2);
    g.InsertE(2, 3);

    cout << "Following is a Topological Sort of\n";
    g.TopologicalSort();
	return 0;
}