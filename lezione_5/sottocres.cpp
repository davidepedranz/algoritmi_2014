//============================================================================
// Name        : sottocres.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Programmazione dinamica - sottoinsieme crescente somma max
//============================================================================

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

// #define TEST

const int VOID = -3;
const int INF = 999999;

int next(int* a, int n, int max, int i) {

	i++;
	while(i < n) {
		if(a[i] > max) {
			return i;
		}
		i++;
	}

	return n;
}

int sottocres(int* a, int n, int i, int current, int _max, int** s) {
	// cout << "sottocres" << " i=" << i << " current=" << current << " _max= " << _max << endl;

	if(i >= n) {
		return 0;
	}

	if(s[i][current] == VOID) {

		// non lo prendo -> passo al prossimo elemento sensato
		int no = sottocres(a, n, next(a, n, current, i), current, _max, s);

		// lo prendo
		int si = sottocres(a, n, next(a, n, a[i], i), a[i], _max, s) + a[i];

		// cout << "calcolato per i=" << i << " si=" << si << " no=" << no << endl;

		s[i][current] = max(no, si);
	}

	return s[i][current];
}

int sottocres(int* a, int n, int max) {
	int** s = new int*[n];

	for(int i = 0; i < n; i++) {
		s[i] = new int[max+1];
		fill(s[i], s[i]+max+1, VOID);
	}

	int result = sottocres(a, n, 0, 0, max, s);

	delete[] s;

	return result;
}


int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	int n;
	in >> n;

	int* a = new int[n];

	for(int i = 0; i < n; i++) {
		in >> a[i];
	}

	#ifdef TEST
	for(int i = 0; i < n; i++) {
		int index = next(a, n, a[i], i);
		cout << "next of " << a[i] << " (pos " << i << ") -> " << a[index] << " (pos " << index << ")\n";
	}
	#endif

	int max = *max_element(a, a+n);

	int result = sottocres(a, n, max);
	out << result << endl;

	delete[] a;

	return 0;
}