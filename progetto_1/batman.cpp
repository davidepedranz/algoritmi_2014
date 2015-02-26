//============================================================================
// Author      : Luca Bosotti, Marco Federici, Davide Pedranz
// Licence     : GPL v2
//============================================================================

#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
using namespace std;

struct nod {
	int index;
	vector<nod*> adj;

	nod(int index) {
		this->index = index;
	}
};

typedef nod* node;
typedef vector<node> graph;

struct collapse {
	node start;
	node end;
	graph* gp;

	collapse(node start, node end, graph* gp) {
		this->start = start;
		this->end = end;
		this->gp = gp;
	}

	~collapse() {
		for(int i = 0; i < gp->size(); i++) {
			delete (*gp)[i];
		}
		delete gp;
	}
};

// funzione che alloca il grafo 
// leggi il file di input e costruisce due grafi, il normale e il trasposto
pair<graph, graph> readGraphs(ifstream& in, int n, int m) {

	// init graphs
	graph dritto, trasposto;
	dritto.resize(n);
	trasposto.resize(n);

	for (int i = 0; i < n; i++) {
		dritto[i] = new nod(i);
		trasposto[i] = new nod(i);
	}

	// read graph from file
	for (int i = 0; i < m; i++) {
		int from, to;
		in >> from >> to;

		// cotruisce grafo dritto
		dritto[from]->adj.push_back(dritto[to]);

		// cotruisce grafo trasposto
		trasposto[to]->adj.push_back(trasposto[from]);
	}

	return make_pair(dritto, trasposto);
}

void deleteGraph(graph& g) {
	for (int i = 0; i < g.size(); i++) {
		delete g[i];
	}
}

void deleteGraphs(graph& dritto, graph& trasposto) {
	deleteGraph(dritto);
	deleteGraph(trasposto);
}

// chiamata ricorsiva -> evita stack esplicito
void topological_dfs(node u, bool* visited, stack<int>* s) {
	visited[u->index] = true;

	for (node v : u->adj) {
		if (!visited[v->index]) {
			topological_dfs(v, visited, s);
		}
	}

	s->push(u->index);
}

// restituisce uno stack con gli indentificatori dei nodi
// l'ordinamento topologico si ottiene estraendo i nodi dallo stack
stack<int>* topologicalSort(graph& g, node start) {

	int size = g.size();
	bool* visited = new bool[size];
	fill(visited, visited + size, false);

	stack<int>* s = new stack<int>;

	// NB: visito solo parte del grafo raggiungibile
	// dal nodo di partenza, il resto NON mi interessa
	topological_dfs(start, visited, s);

	return s;
}

// chiamata ricorsiva delle componenti connesse
void cc_dfs(node u, int conta, int* componentiConnesse) {
	componentiConnesse[u->index] = conta;

	for(node v : u->adj) {
		if(componentiConnesse[v->index] == 0) {
			cc_dfs(v, conta, componentiConnesse);
		}
	}
}

// restistisce array di identificatori delle componenti connesse
int* connectedComponents(graph& g, stack<int>* s) {
	int size = g.size();

	int conta = 0;
	int* componentiConnesse = new int[size];
	fill(componentiConnesse, componentiConnesse + size, 0);

	while(!s->empty()){
		int i = s->top();
		s->pop();

		if(componentiConnesse[i] == 0){
			conta++;
			cc_dfs(g[i], conta, componentiConnesse);
		}
	}

	return componentiConnesse;
}

// componenti fortemente connesse
int* ccf(graph& dritto, graph& trasposto, node start){

	// Creo lo stack e gli inserisco l'ordine topologico del grafo
	stack<int>* s = topologicalSort(dritto, start);

	return connectedComponents(trasposto, s);
}

// collassa le componenti fortemente connesse
collapse* collapse_ccf(graph& g, graph& t, node start, node end) {
	int size = g.size();

	// calcolo ccf
	int* ids = ccf(g, t, start);

	// numero di componenti fortemente connesse
	// NB: +1 perchè possono esserci dei nodi non esaminati
	// per le componenti connesse (es non raggiunbili dalla partenza)
	// con id ancora a zero
	int n_comp = *max_element(ids, ids+size) + 1;

	graph* collapsed_graph = new vector<node>;
	collapsed_graph->resize(n_comp);

	for (int i = 0; i < n_comp; i++) {
		(*collapsed_graph)[i] = new nod(i);
	}

	// rimappo inizio e fine
	node new_start = (*collapsed_graph)[ids[start->index]];
	node new_end = (*collapsed_graph)[ids[end->index]];

	// array per visita
	bool* visited = new bool[size];
	fill(visited, visited+size, false);

	queue<node> q;
	q.push(start);

	// bfs modificata
	while(!q.empty()) {
		node u = q.front();
		q.pop();

		visited[u->index] = true;
		int current_id = ids[u->index];

		// visito vicini
		for(node v : u->adj) {
			int target_id = ids[v->index];

			// se gli id sono diversi, sto passando a una nuova ccd
			// quindi salvo questo arco
			// altrimenti sono all'interno della stessa ccf
			if (current_id != target_id) {
				(*collapsed_graph)[current_id]->adj.push_back((*collapsed_graph)[target_id]);
			}

			if(!visited[v->index]) {
				q.push(v);
				visited[v->index] = true;
			}
		}
	}

	delete[] ids;
	delete[] visited;
	return new collapse(new_start, new_end, collapsed_graph);
}

// funzione che calcola il numero di cammini da start a end
// faccio visita in base a ordinamento topologico del grafo
// delle ccf collassate
// NB: questo grafo è certamente aciclico e connesso
int numeroCammini(graph& g, node start, node end) {
	stack<int>* ordineTopologico = topologicalSort(g, start);

	int size = g.size();
	int* cammini = new int[size];
	fill(cammini, cammini+size, 0);

	//setto il numero di cammini del nodo start a 1
	cammini[start->index] = 1;

	while(!ordineTopologico->empty()) {

		//estraggo e rimuovo il primo nodo dello stack
		int nodoEstratto = ordineTopologico->top();
		ordineTopologico->pop();

		// se ho trovato il nodo finale, esco dal ciclo
		if(nodoEstratto == end->index){
			break;
		}

		// per ogni nodo adiacente a quello estratto
		for(node n : g[nodoEstratto]->adj) {
			//sommo il valore presente nel nodo estratto
			cammini[n->index] += cammini[nodoEstratto];
		}
	}

	int risultato = cammini[end->index];

	delete[] cammini;
	return risultato;
}

int main() {
	
	// inizializzo stream
	ifstream in("input.txt");
	ofstream out("output.txt");

	// leggo informazioni principali dal file
	int n, m, batCaverna, batCasa;
	in >> n >> m >> batCaverna >> batCasa;

	// Inizializziamo i grafi
	pair<graph, graph> graphs = readGraphs(in, n, m);
	graph dritto = graphs.first;
	graph trasposto = graphs.second;

	// salvo nodi di partenza e di arrivo
	node start = dritto[batCaverna];
	node end = dritto[batCasa];

	// collasso le componenti connesse
	collapse* c = collapse_ccf(dritto, trasposto, start, end);
	node new_start = c->start;
	node new_end = c->end;
	graph new_graph = *(c->gp);

	// calcolo i possibili percorsi
	int result = numeroCammini(new_graph, new_start, new_end);

	// write result
	out << result << endl;

	// pulisco memoria
	delete c;
	deleteGraphs(dritto, trasposto);

	return 0;
}
