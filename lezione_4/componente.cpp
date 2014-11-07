//============================================================================
// Name        : componente.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : componente fortemente conessa più grande
//============================================================================

#include <vector>
#include <stack>
#include <fstream>
#include <iostream>
using namespace std;

struct node {
	bool visited = false;
	int value;
	int id = 0;
	vector<int> adj;
};

void ts_dfs(vector<node*>& graph, node* u, stack<int>& s) {
	u->visited = true;
	for(int i : u->adj) {
		node* v = graph[i];
		if(!v->visited) {
			ts_dfs(graph, v, s);
		}
	}
	s.push(u->value);
}

void topSort(vector<node*>& graph, stack<int>& s) {
	for(node* u : graph) {
		if(!u->visited) {
			ts_dfs(graph, u, s);
		}
	}
}

int ccdfs(vector<node*>& graph, int id, node* u, int& count) {
	u -> id = id;
	for(int i : u->adj) {
		node* v = graph[i];
		if(v->id == 0) {
			ccdfs(graph, id, v, ++count);
		}
	}
}

int max_cc(vector<node*>& graph, stack<int>& s) {
	int couter = 0;
	int maxDim = 0;

	while(!s.empty()) {
		int count = 1;

		int i = s.top();
		s.pop();

		node* n = graph[i];
		
		if(n->id == 0) {
			couter++;
			ccdfs(graph, couter, n, count);

			maxDim = max(maxDim, count);
		}
	}

	return maxDim;
}

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	// read # of nodi & archi from file
	int nodi, archi;
	in >> nodi >> archi;

	// init graph
	vector<node*> graph;
	vector<node*> trasposto;
	graph.resize(nodi);
	trasposto.resize(nodi);

	for(int i = 0; i < nodi; i++) {
		// grafo
		graph[i] = new node;
		graph[i]->value = i;

		// trasposto
		trasposto[i] = new node;
		trasposto[i]->value = i;

		// trasposto[i] = graph[i];
	}

	// read graph from file
	for(int i = 0; i < archi; i++) {
		int from, to;
		in >> from >> to;
		graph[from]->adj.push_back(to);

		// trasposto
		trasposto[to]->adj.push_back(from);
	}

	stack<int> s;
	topSort(graph, s);

	// scc
	int max = max_cc(trasposto, s);

	// dealloc nodes
	for(int i = 0; i < nodi; i++) {
		delete graph[i];
		delete trasposto[i];
	}

	out << max << endl;

	return 0;
}