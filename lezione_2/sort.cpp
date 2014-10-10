//============================================================================
// Name        : sort.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Lab_2, Task_1: array sort
//============================================================================

#include <fstream>
using namespace std;

void merge(int* a, int* b, int start, int end, int middle) {
	if(start < end) {

		int i = start;
		int j = middle + 1;
		int k = start;

		while(i <= middle && j <= end) {
			if(a[i] <= a[j]) {
				b[k] = a[i];
				i++;
			} else {
				b[k] = a[j];
				j++;
			}
			k++;
		}

		while(i <= middle) {
			b[k] = a[i];
			i++;
			k++;
		}

		while(j <= end) {
			b[k] = a[j];
			j++;
			k++;
		}

		// reverse in original array
		for(int m = start; m <= end; m++) {
			a[m] = b[m];
		}
	}
}

// merge sort
void mergeSort(int* a, int* b, int start, int end) {
	if(start < end) {
		int m = (start + end) / 2;
		mergeSort(a, b, start, m);
		mergeSort(a, b, m + 1, end);
		merge(a, b, start, end, m);
	}
}

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	// read array dim
	int n;
	in >> n;

	int* array = new int[n];
	int* support = new int[n];

	for(int i = 0; i < n; i++) {
		// read next element
		in >> array[i];
	}

	mergeSort(array, support, 0, n-1);

	for(int i = 0; i < n; i++) {
		out << array[i] << " ";
	}

	delete[] support;
	delete[] array;

	return 0;
}