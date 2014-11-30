//============================================================================
// Name        : zaino.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Programmazione Dinamica: zaino
//============================================================================

#include <fstream>
#include <algorithm>
#include <cstdlib>
using namespace std;

int zaino(int* pesi, int* valori, int n, int c) {

	// tabella per la programmazione dinamica
	// ridotta a 2 righe per risparmiare memoria e tempo
	int** s = new int*[2];
	s[0] = new int[c+1];
	s[1] = new int[c+1];

	fill(s[0], s[0]+c+1, 0);
	fill(s[1], s[1]+c+1, 0);

	int i;

	for(i = 0; i < n; i++) {
		int ii = abs(i-1) % 2;

		// riempio tutta la riga
		// NB: alcune caselle possono NON avere senso
		// in questo caso ci sarà scritto 0
		for(int j = 0; j < c+1; j++) {

			int non_lo_prendo = s[ii][j];
			int lo_prendo = (j + pesi[i] <= c) ? s[ii][j + pesi[i]] + valori[i] : -99999999;

			s[i % 2][j] = max(lo_prendo, non_lo_prendo);
		}
	}

	i = abs(i-1) % 2;

	// il risultato è il massimo valore che posso fare
	// considerando tutti gli oggetti, quindi si trova
	// sull'ultima riga
	int result = s[i][0];
	for(int j = 1; j < c+1; j++) {
		result = max(s[i][j], result);
	}

	
	delete[] s[0];
	delete[] s[1];
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
