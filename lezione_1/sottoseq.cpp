//============================================================================
// Name        : sottoseq.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Lab_1, Task_1: sottosequenza
//============================================================================

#include <fstream>
using namespace std;

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	int maxSum = 0;
	int currentSum = 0;

	// read array dim
	int n;
	in >> n;

	int tmp;

	for(int i = 0; i < n; i++) {
		// read next element
		in >> tmp;

		// compute max subsequence
		currentSum = max(currentSum + tmp, 0);
		maxSum = max(currentSum, maxSum);
	}

	// return
	out << maxSum << endl;

	return 0;
}