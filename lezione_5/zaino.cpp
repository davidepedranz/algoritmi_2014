//============================================================================
// Name        : zaino.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Programmazione Dinamica: zaino
//============================================================================

#include <fstream>
#include <algorithm>
using namespace std;

const int VOID = -3;
const int INF = 99999999;

int zaino(int** s, int* pesi, int* valori, int i, int c) {

	if (c < 0) {
		return -INF;
	}

	if (c == 0 || i < 0) {
		return 0;
	}

	if (s[i][c] == VOID) {
		int prendo = zaino(s, pesi, valori, i-1, c - pesi[i]) + valori[i];
		int no = zaino(s, pesi, valori, i-1, c);
		s[i][c] = max(prendo, no);
	}

	return s[i][c];
}

int zaino(int* pesi, int* valori, int n, int c) {

	int** s = new int*[n];
	for(int i = 0; i < n; i++) {
		s[i] = new int[c+1];
		fill(s[i], s[i] + c + 1, VOID);
	}

	int result = zaino(s, pesi, valori, n-1, c);

	for(int i = 0; i < n; i++) {
		delete[] s[i];
	}
	delete[] s;

	return result;
}

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	// leggo capacita dello zaino e numero di oggetti
	int c, n;
	in >> c >> n;

	// alloco array per gli oggetti
	int* pesi = new int[n];
	int* valori = new int[n];

	int p, v;
	for(int i = 0; i < n; i++) {
		in >> p >> v;
		pesi[i] = p;
		valori[i] = v;
	}

	int result = zaino(pesi, valori, n, c);
	out << result << endl;

	delete[] pesi;
	delete[] valori;

	return 0;
}