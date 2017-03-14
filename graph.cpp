#include <iostream>
#include <list>
#include <queue>
using namespace  std;

class Graph{
	private:
		int V;
		list<int> *adj;
		vector<int> InDegree();
	public:
		Graph(int v);
		void InsertE(int v, int w);
		void TopologicalSort();

};

Graph::Graph(int v){
	V = v;
	adj = new list<int>[v];
}

void Graph::InsertE(int w, int v){
	adj[w].push_back(v);     
}

vector<int> Graph::InDegree(){
	vector<int> indegree (V,0);
	for(int k = 0; k < V; k++){

		for(list<int>::iterator i = adj[k].begin(); i != adj[k].end(); i++)
	    	indegree[*i]++;

	}
	return indegree;

}
void Graph::TopologicalSort(){

	/* Cria um vetor para registar o resultado da ordenacao */
	vector<int> order;

	/* Cria uma fila de espera */
	queue<int> queue;

	/* Cria um vetor em que guarda o numero de
	 * arcos de entrada de cada vertice do grafo */
	vector<int> indegree = InDegree();

	/* Adiciona a lista de espera todos os verices sem arcos
	 * de entrada */		
	for(int i = 0; i < V; i++)
		if(indegree[i] == 0)
			queue.push(i);

	int cnt_visit = 0;     // Indica o numero de vertices visitados

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
			if(--indegree[*i] == 0)
				queue.push(*i);
			cnt_visit++;
		}
		
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
	Graph g(6);
    g.InsertE(5, 2);
    g.InsertE(5, 0);
    g.InsertE(4, 0);
    g.InsertE(4, 1);
    g.InsertE(2, 3);
    g.InsertE(3, 1);
 
    cout << "Following is a Topological Sort of\n";
    g.TopologicalSort();
	return 0;
}