//============================================================================
// Name        : numcammini.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Lab_3, Task_3: numero cammini minimi
//============================================================================

#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct node {
	bool visited = false;
	int inc;
	int pos;
	int order;
	vector<int> adj;

	node(int i) {
		pos = i;
	}
};

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	// read input from file
	int nodi, archi, start, end;
	in >> nodi >> archi >> start >> end;

	// init graph
	vector<node*> graph;
	graph.resize(nodi);

	for(int i = 0; i < nodi; i++) {
		graph[i] = new node(i);
	}

	// read graph from file
	int from, to;
	for(int i = 0; i < archi; i++) {
		in >> from >> to;
		graph[from] -> adj.push_back(to);
	}

	int distMin, nCammini;

	queue<node*> q;	

	// bfs -> add first node
	graph[start] -> inc = 1;
	graph[start] -> order = 0;
	q.push(graph[start]);

	// bfs
	while(!q.empty()) {
		node* current = q.front();
		q.pop();

		if(current->pos == end) {

			distMin = current->order;
			nCammini = current->inc;

			// esci brutalmente
			break;
		}

		for(int el : current->adj) {
			node* n = graph[el];

			if(!n->visited) {
				n->visited = true;
				n->inc = current->inc;
				n->order = current->order + 1;
				q.push(n);
			} else {
				if(n->order == (current->order + 1)) {
					n->inc += current->inc;
				}
			}
		}
	}

	// dealloco nodi
	for(int i = 0; i < nodi; i++) {
		delete graph[i];
	}
	
	// output
	out << distMin << " " << nCammini << endl;

	return 0;
}