//============================================================================
// Name        : camminolungo.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : grafo aciclico orientato -> cammino più lungo
//============================================================================

#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct nod {
	int key;
	int value;
	vector<nod*> adj;

	nod(int key) {
		this->key = key;
		this->value = key;
	}

	nod(int key, int value) {
		this->key = key;
		this->value = value;
	}
};

typedef nod* node;
typedef vector<node> graph;


int max_dfs(node u, int* a) {
	if(a[u->key] != 0) {
		return a[u->key];
	}

	// nodi consecutivi raggiungibili da questo
	int m = 0;

	// dfs
	for(node v : u->adj) {
		a[v->key] = max_dfs(v, a);

		// ho trovato un cammino più lungo
		if (a[v->key] > m) {
			m = a[v->key];
		}
	}

	// questo nodo è raggiungibile da se stesso
	m++;

	return m;
}

int max_walk(graph& g) {
	int n = g.size();

	// "# nodi consecutivi raggiungibili" da quello con chiave i
	int* a = new int[n];
	fill(a, a+n, 0);

	// programmazione dinamica: dfs da tutti i nodi
	// ma memorizzo ogni volta il numero di nodi consecutivi
	// raggiungibili dal corrente
	for(int i = 0; i < n; i++) {
		a[i] = max_dfs(g[i], a);
	}

	// ritorno lughezza cammino più lungo = max 
	// nodi consecutivi raggiungibili - 1 (il corrente)
	int m = *max_element(a, a+n) - 1;

	delete[] a;
	return m;
}

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	// read # of nodi & archi from file
	int n, m;
	in >> n >> m;

	// init graph
	graph g;
	g.resize(n);

	for(int i = 0; i < n; i++) {
		g[i] = new nod(i);
	}

	// read graph from file
	for(int i = 0; i < m; i++) {
		int from, to;
		in >> from >> to;
		g[from]->adj.push_back(g[to]);
	}

	out << max_walk(g) << endl;

	// dealloc nodes
	for(int i = 0; i < n; i++) {
		delete g[i];
	}

	return 0;
}
