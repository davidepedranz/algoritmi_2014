//============================================================================
// Name        : topporder.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : ordinamento topologico
//============================================================================

#include <vector>
#include <stack>
#include <fstream>
using namespace std;

struct node {
	bool visited = false;
	int value;
	vector<int> adj;
};

void ts_dfs(vector<node*>& graph, node* u, stack<node*>& s) {
	u->visited = true;
	for(int i : u->adj) {
		node* v = graph[i];
		if(!v->visited) {
			ts_dfs(graph, v, s);
		}
	}
	s.push(u);
}

void topSort(vector<node*>& graph, stack<node*>& s) {
	for(node* u : graph) {
		if(!u->visited) {
			ts_dfs(graph, u, s);
		}
	}
}

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	// read # of nodi & archi from file
	int nodi, archi;
	in >> nodi >> archi;

	// init graph
	vector<node*> graph;
	graph.resize(nodi);
	for(int i = 0; i < nodi; i++) {
		graph[i] = new node;
		graph[i]->value = i;
	}

	// read graph from file
	for(int i = 0; i < archi; i++) {
		int from, to;
		in >> from >> to;
		graph[from]->adj.push_back(to);
	}

	stack<node*> s;
	topSort(graph, s);

	while(!s.empty()) {
		node* n = s.top();
		out << n->value << " ";
		s.pop();
	}
	out << endl;

	// dealloc nodes
	for(int i = 0; i < nodi; i++) {
		delete graph[i];
	}

	return 0;
}