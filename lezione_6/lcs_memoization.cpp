//============================================================================
// Name        : lcs.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Sottosequenza comune massimale (con memoization)
//============================================================================

#include <fstream>
#include <algorithm>
using namespace std;

const int VOID = -1;

int** alloc_matric(int n, int m) {
	int** D = new int*[n];
	for(int i = 0; i < n; i++) {
		D[i] = new int[m];
		fill(D[i], D[i] + m, VOID);
	}
	return D;
}

void dealloc_matrix(int** D, int n) {
	for(int i = 0; i < n; i++) {
		delete[] D[i];
	}
	delete[] D;
}

int lcs(int** D, string& p, string& t, int i, int j) {
	
	if(i < 0 || j < 0) {
		return 0;
	}

	if(D[i][j] == VOID) {
		if(p[i] == t[j]) {
			D[i][j] = lcs(D, p, t, i-1, j-1) + 1;
		} else {
			D[i][j] = max(lcs(D, p, t, i-1, j), lcs(D, p, t, i, j-1));
		}
	}

	return D[i][j];
}

int lcs(string& p, string& t) {

	int n = p.size();
	int m = t.size();

	int** D = alloc_matric(n, m);
	int res = lcs(D, p, t, n-1, m-1);
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
