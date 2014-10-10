//============================================================================
// Name        : sortpesato.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Lab_2, Task_3: sortpesato
//============================================================================

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

void printArray(int* array, int n) {
	cout << "Array: ";
	for(int i = 0; i < n; i++) {
		cout << array[i] << " ";
	}
	cout << endl;
}

void swap(int& a, int& b) {
	int tmp = a;
	a = b;
	b = tmp;
}

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

// numero di scambi fatti da algoritmo selectionSort
int computeTurns(int* a, int* o, int n) {
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

// TODO: implement
int computeCost(int* a, int* o, int n) {

	return 0;
}

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	// read data
	int n;
	in >> n;

	int* array = new int[n];
	int* ordered = new int[n];

	for(int i = 0; i < n; i++) {
		in >> array[i];
		ordered[i] = array[i];
	}

	sort(ordered, ordered + n);

	int turns = computeTurns(array, ordered, n);
	int price = computeCost(array, ordered, n);

	// write output
	out << turns << " " << price << endl;

	// clean memory
	delete[] array;

	return 0;
}
