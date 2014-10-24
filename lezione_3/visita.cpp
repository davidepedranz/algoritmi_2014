//============================================================================
// Name        : visita.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Lab_3, Task_1: visita grafo
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct node {
	bool visited = false;
	vector<int> adj;
};

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	int nodi, archi, start;
	in >> nodi >> archi >> start;

	vector<node> graph;
	graph.resize(nodi);

	// read graph from file
	for(int i = 0; i < archi; i++) {
		int from, to;
		in >> from >> to;
		graph[from].adj.push_back(to);
	}

	int counter = 1;
	queue<node> q;

	// bfs -> add first node
	q.push(graph[start]);
	graph[start].visited = true;

	// bfs
	while(!q.empty()) {
		node next = q.front();
		q.pop();

		for(int el : next.adj) {
			if(!graph[el].visited) {
				q.push(graph[el]);
				graph[el].visited = true;
				counter++;
			}
		}
	}

	// output
	out << counter << endl;

	return 0;
}