//============================================================================
// Name        : samarcanda.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Samarcanda
//============================================================================

#include <iostream>
#include <utility>
using namespace std;

pair<int,int> samarcanda_pro(int* v, int n) {
	int minimo = v[0];
	int guadagno = 0;
	int k, j = 0;

	for(int i = 1; i < n; i++) {
		minimo = min(minimo, v[i]);

		if((v[i] - minimo) > guadagno) {
			guadagno = v[i] - minimo;
			j = i;
			k = minimo;
		}
	}

	return make_pair(k, v[j]);
}

int samarcanda(int* v, int n) {
	int minimo = v[0];
	int guadagno = 0;

	for(int i = 1; i < n; i++) {
		minimo = min(minimo, v[i]);
		guadagno = max(guadagno, v[i] - minimo);
	}

	return guadagno;
}

void print(int* a, int n) {
	cout << "array: ";
	for(int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int main() {

	int a[] = {3, 1, 4, 8, 2, 5, 12, 4, 7, 9};
	int b[] = {2, 2, 5, 2, 2, 5, 7, 2, 1, 1};
	int c[] = {2, 50, 3, 1, 2, 4, 5, 1, 0, 1};

	print(a, 8);
	cout << "RESULT: " << samarcanda(a, 10) << " ---> " << samarcanda_pro(a, 10).first << " " << samarcanda_pro(a, 10).second << endl;

	print(b, 8);
	cout << "RESULT: " << samarcanda(b, 10) << " ---> " << samarcanda_pro(b, 10).first << " " << samarcanda_pro(b, 10).second << endl;

	print(c, sizeof(c)/sizeof(int));
	cout << "RESULT: " << samarcanda(c, 10) << " ---> " << samarcanda_pro(c, 10).first << " " << samarcanda_pro(c, 10).second << endl;
	
	return 0;
}