//============================================================================
// Name        : diametro.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Lab_3, Task_2: diametro grafo
//============================================================================

#include <fstream>
#include <vector>
#include <queue>
using namespace std;

const int INF = -1;

struct node {
	int value;
	vector<int> adj;
};

int erdosMax(vector<node>& graph, int start) {
	queue<node> q;	
	int* distances = new int[graph.size()];

	for(int i = 0; i < graph.size(); i++) {
		distances[i] = INF;
	}

	int maxErd = 0;

	// bfs -> add first node
	q.push(graph[start]);
	distances[start] = 0;

	// bfs
	while(!q.empty()) {
		node next = q.front();
		q.pop();

		for(int el : next.adj) {
			if(distances[el] == INF) {
				distances[el] = distances[next.value] + 1;
				q.push(graph[el]);

				// salvo distanza di start dal nodo + lontano
				maxErd = max(maxErd, distances[el]);
			}
		}
	}

	delete[] distances;

	return maxErd;
}

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	// read # of nodi & archi from file
	int nodi, archi;
	in >> nodi >> archi;

	// init graph
	vector<node> graph;
	graph.resize(nodi);
	for(int i = 0; i < nodi; i++) {
		graph[i].value = i;
	}

	// read graph from file
	for(int i = 0; i < archi; i++) {
		int from, to;
		in >> from >> to;
		graph[from].adj.push_back(to);
		graph[to].adj.push_back(from);
	}

	int diametro = 0;

	// faccio visita bfs in stile Erdos da ogni nodo
	// e salvo la distanza massima tra due nodi
	for(int i = 0; i < nodi; i++) {
		int current = erdosMax(graph, i);
		diametro = max(diametro, current);
	}

	// output
	out << diametro << endl;

	return 0;
}