//============================================================================
// Name        : massimale.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Massimale
//============================================================================

#include <iostream>
#include <utility>
using namespace std;

pair<int, int> max(int* a, int i, int j) {
	if(i >= j) {
		return make_pair(a[i], 1);
	} else {
		pair<int, int> p1 = max(a, i, (j+i)/2);
		pair<int, int> p2 = max(a, (j+i)/2 + 1, j);

		if(p1.first == p2.first) {
			return make_pair(p1.first, p1.second + p2.second);
		} else {
			return (p1.second > p2.second ? p1 : p2);
		}
	}
}

int max(int* a, int n) {
	pair<int,int> p = max(a, 0, n-1);

	int counter = 0;
	for(int i = 0; i < n; i++) {
		if(a[i] == p.first) {
			counter++;
		}
	}

	if(counter > n/2) {
		return p.first;
	} else {
		return -1;
	}
}

void print(int* a, int n) {
	cout << "array: ";
	for(int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	cout << endl;
}

int main() {

	int a[] = {2, 3, 5, 2, 2, 5, 7, 2};
	int b[] = {2, 2, 5, 2, 2, 5, 7, 2};

	print(a, 8);
	cout << "RESULT: " << max(a, 8) << endl;

	print(b, 8);
	cout << "RESULT: " << max(b, 8) << endl;
	
	return 0;
}