//============================================================================
// Name        : hateville.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Hateville - programmazione dinamica
//============================================================================

#include <fstream>
using namespace std;

const int EMPTY = -1;

int* alloc(int n) {
	int* a = new int[n];
	for(int i = 0; i < n; i++) {
		a[i] = EMPTY;
	}
	return a;
}

int hateville(int* donazioni, int n, int i, int* a) {
	if (i >= n) {
		return 0;
	}

	if(a[i] == EMPTY) {
		a[i] = max(hateville(donazioni, n, i+2, a) + donazioni[i], hateville(donazioni, n, i+1, a));
	}

	return a[i];
}

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	int n;
	in >> n;

	int* donazioni = new int[n];
	
	for(int i = 0; i < n; i++) {
		in >> donazioni[i];
	}

	int* a = alloc(n);

	int max = hateville(donazioni, n, 0, a);
	out << max << endl;

	delete[] a;
	delete[] donazioni;

	return 0;
}