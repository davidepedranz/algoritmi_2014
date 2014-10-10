//============================================================================
// Name        : intervalli.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Lab_2, Task_2: intervalli
//============================================================================

#include <fstream>
#include <utility>
#include <algorithm>
using namespace std;

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	// read array dim
	int n;
	in >> n;

	// alloc space for pairs
	pair<int,int>* array = new pair<int,int>[n];

	// read pairs
	for(int i = 0; i < n; i++) {
		in >> array[i].first >> array[i].second;
	}

	// sort pairs
	sort(array, array + n);

	int maxGap = 0;
	pair<int,int> el;

	int gap;
	int last = array[0].second;

	for(int i = 1; i < n; i++) {

		// compute last covered number
		last = max(last, array[i-1].second);

		// compute gap
		gap = array[i].first - last;

		// if current gap > maxGap, remember this gap as max
		if(gap > maxGap) {
			maxGap = max(maxGap, gap);
			el.first = last;
			el.second = array[i].first;
		}

	}

	// return output
	if(maxGap == 0) {
		out << "0" << endl;
	} else {
		out << el.first << " " << el.second << endl;
	}

	delete[] array;

	return 0;
}