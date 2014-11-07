//============================================================================
// Name        : somma_max.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Somma Massima - programmazione dinamica
//============================================================================

#include <fstream>
using namespace std;

const int EMPTY = -1;
const int INF = 999999;

int** alloc(int n, int m) {
	int** matrix = new int*[n];
	for(int i = 0; i < n; i++) {
		matrix[i] = new int[m];
		for(int j = 0; j < m; j++) {
			matrix[i][j] = EMPTY;
		}
	}
	return matrix;
}

void dealloc(int** matrix, int n) {
	for(int i = 0; i < n; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

int zaino(int* a, int n, int i, int w, int** matrix) {
	if (i == n || w == 0) {
		return 0;
	}

	if (w < 0) {
		return -INF;
	}

	if(matrix[i][w] == EMPTY) {
		matrix[i][w] = max(zaino(a, n, i, w - a[i], matrix) + a[i], zaino(a, n, i + 1, w, matrix));
	}

	return matrix[i][w];
}

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	int n, w;
	in >> n >> w;

	int* a = new int[n];

	for(int i = 0; i < n; i++) {
		in >> a[i];
	}

	int** matrix = alloc(n, w+1);

	int somma = zaino(a, n, 0, w, matrix);
	out << somma << endl;

	dealloc(matrix, n);
	delete[] a;

	return 0;
}