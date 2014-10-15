//============================================================================
// Name        : sortpesato.cpp
// Author      : Davide Pedranz
// Version     : 1n
// Licence     : GPL v2
// Description : See statement.
//============================================================================

// #include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// struct Result {
// 	int swaps;
// 	int cost;

// 	Result() {
// 		swaps = 0;
// 		cost = 0;
// 	}
// };

struct Block {
	int value;
	bool visited;

	Block(int v) {
		visited = false;
		value = v;
	}

	int getValue() {
		visited = true;
		return value;
	}
};

// returns min element index
int posMin(int* a, int start, int end) {
	int min = a[start];
	int pos = start;

	for(int i = start + 1; i < end; i++) {
		if(a[i] < min) {
			min = a[i];
			pos = i;
		}
	}

	return pos;
}


// numero di scambi fatti da algoritmo selectionSort (mettendo minimo in cima)
int computeSwaps(int* a, int n) {
	int swaps = 0;

	int indexMin;
	for(int i = 0; i < n; i++) {
		indexMin = posMin(a, i, n);
		if(indexMin != i) {
			swap(a[i], a[indexMin]);
			swaps++;
		}
	}
	return swaps;
}

// ======================================================================================================================
// ======================================================================================================================

// void printArray(int* array, int n) {
// 	for(int i = 0; i < n; i++) {
// 		cout << array[i] << " ";
// 	}
// 	cout << endl;
// }

// void printVV(vector<vector<int>>& vv) {
// 	int i = 1;
// 	for(vector<int> v : vv) {
// 		cout << "vettore " << i++ << ":\t";
// 		for(int el : v) {
// 			cout << el << " ";
// 		}
// 		cout << endl;
// 	}
// }

// void printV(vector<int>& v) {
// 	for(int el : v) {
// 		cout << el << " ";
// 	}
// 	cout << endl;
// }

// wrapper
int computeCost(int* a, int n) {
	Block** b = new Block*[n+1];

	vector<vector<int>> vv;

	for(int i = 1; i <= n; i++) {
		b[i] = new Block(a[i-1]);
	}

	// printArray(a, n);
	// for(int i = 1; i <= n; i++) {
	// 	cout << b[i] -> value << " ";
	// }
	// cout << endl;

	for(int i = 1; i <= n; i++) {
		if(!b[i]->visited && b[i]->value != i) {
			vector<int> v;

			Block* current = b[i];
			int value = current->getValue();
			v.push_back(value);

			Block* next = b[value];

			while(!next->visited) {
				int val = next->getValue();
				v.push_back(val);
				next = b[val];
			}

			vv.push_back(v);
		}
	}

	// printVV(vv);

	int totalCost = 0;

	for(auto v : vv) {
		// cout << endl;
		// printV(v);

		int sum = 0;
		int min = n+10;
		for(int el : v) {
			sum += el;
			if(el < min) {
				min = el;
			}
		}

		int costA = sum - min + min * (v.size() - 1);
		// cout << "cost A: " << costA << endl;

		int costB = sum - min + 1 * (v.size() - 1) + 2 * (1 + min);
		// cout << "cost B: " << costB << endl;

		int realCost = costA < costB ? costA : costB;
		// cout << "realCost: " << realCost << endl;

		totalCost += realCost;
	}

	for(int i = 0; i < n; i++) {
		delete b[i];
	}
	delete[] b;

	return totalCost;
}

// ======================================================================================================================
// ======================================================================================================================

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	// read data
	int n;
	in >> n;

	int* a = new int[n];
	int* b = new int[n];

	// read array from input file
	for(int i = 0; i < n; i++) {
		in >> a[i];
		b[i] = a[i];
	}

	int swaps = computeSwaps(a, n);
	int cost = computeCost(b, n);

	// return
	out << swaps << " " << cost << endl;

	delete[] a;
	delete[] b;

	return 0;
}