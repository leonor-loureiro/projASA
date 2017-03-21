#include <iostream>
#include "graph.hpp"
using namespace  std;



Edge::Edge(int pre, int suc){
	predecessor = pre;
	successor = suc;
}



Graph::Graph(int v){
	V = v;
	adj = new list<int>[v];
	indegree = new int[v];
	for(int i = 0; i < v; i++)
		indegree[i]=0;
}

void Graph::insertEdge(Edge e){
	adj[e.predecessor].push_back(e.successor);
	indegree[e.successor]++;
}


vector<int> Graph::topologicalSort(){

	/* Cria um vetor para registar o resultado da ordenacao */
	vector<int> order;

	/* Armazena o vertice sem arcos de entrada */
	queue<int> queue;

	/* Flag para insufficient*/
	bool insufficient = false;

	int cnt_visit = 0;     // Indica o numero de vertices visitados


	/* Adiciona a lista de espera todos os verices sem arcos
	 * de entrada */
	for(int i = 0; i < V; i++){

		if(indegree[i] == 0){
			if (!queue.empty()){
				insufficient = true;
			}
			queue.push(i);

		}
	}


	

	/* Retira, um a um os vertices da fila de espera e adiciona
	 * os vertices adjacente quando o seu in degree atinge o zero */
	while(!queue.empty()){

		/* Remove o primeiro vertice da fila de espera e adiciona-o
		 * a ordem topologica */
		int x = queue.front();
		queue.pop();
		order.push_back(x);
		cnt_visit++;           //incrementa o numero de vertices visitados

		/*Itera os todos vertices adjacentes ao vertice x e
		 * decrementa o seu indegree numa unidade */
		for(list<int>::iterator i = adj[x].begin(); i!=adj[x].end(); i++){
			if(--indegree[*i] == 0){
				if(!queue.empty()){
					insufficient = true;
				}
				queue.push(*i);
				
				//cout << cnt_visit<< '\n';
			}
			
		}

	}

	/* Verifica se encontrou um ciclo */
	if(cnt_visit!=V){
		cout << "Incoerente" << endl;
		return vector<int> ();
	}

	/* Verifica se o grafo nao tem uma unica ordenacao possivel */
	if(insufficient){
		cout << "Insuficiente" << endl;
		return vector<int> ();
	}

	return order;
}
