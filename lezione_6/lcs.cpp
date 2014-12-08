//============================================================================
// Name        : lcs.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Sottosequenza comune massimale (programmazione dinamica)
//============================================================================

#include <fstream>
using namespace std;

int** alloc_matric(int n, int m) {
	int** D = new int*[n];
	for(int i = 0; i < n; i++) {
		D[i] = new int[m];
	}
	return D;
}

void dealloc_matrix(int** D, int n) {
	for(int i = 0; i < n; i++) {
		delete[] D[i];
	}
	delete[] D;
}

int lcs(string& p, string& t) {

	int n = p.size();
	int m = t.size();

	int** D = alloc_matric(n + 1, m + 1);

	for(int i = 0; i < n + 1; i++) {
		D[i][0] = 0;
	}

	for(int j = 0; j < m + 1; j++) {
		D[0][j] = 0;
	}
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(p[i] == t[j]) {
				D[i+1][j+1] = D[i][j] + 1;
			} else {
				D[i+1][j+1] = max(D[i+1][j], D[i][j+1]);
			}
		}
	}

	int res = D[n][m];

	dealloc_matrix(D, n);
	return res;
}

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	string s1;
	string s2;

	in >> s1;
	in >> s2;

	int res = lcs(s1, s2);
	out << res << endl;

	in.close();
	out.close();

	return 0;
}
