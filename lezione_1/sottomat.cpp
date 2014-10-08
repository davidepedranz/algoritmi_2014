//============================================================================
// Name        : sottomat.cpp
// Author      : Davide Pedranz
// Version     : 3
// Licence     : GPL v2
// Description : Lab_1, Task_3: sottomatrice massima
//============================================================================

#include <iostream>
#include <fstream>
using namespace std;

int** alloc(int r, int c) {
	int** matrix = new int*[r];

	for (int i = 0; i < r; i++) {
		matrix[i] = new int[c];
	}

	return matrix;
}

int** readMatrix(ifstream& in, int r, int c) {
	int** matrix = new int*[r];

	for (int i = 0; i < r; i++) {
		matrix[i] = new int[c];

		for (int j = 0; j < c; j++) {
			in >> matrix[i][j];
		}
	}

	return matrix;
}

void deleteMatrix(int** matrix, int r) {
	for (int i = 0; i < r; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}

void printMatrix(int** matrix, int r, int c) {
	cout << "matrix:" << endl;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
}

int sum(int** matrix, int startRow, int startCol, int endRow, int endCol) {
	int s = 0;

	for (int i = startRow; i <= endRow; i++) {
		for (int j = startCol; j <= endCol; j++) {
			s += matrix[i][j];
		}
	}

	return s;
}

int maxMatrix(int** matrix, int r, int c) {
	int maxMatrix = 0;
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			maxMatrix = max(maxMatrix, matrix[i][j]);
		}
	}
	return maxMatrix;
}

int solve_1(int** matrix, int r, int c) {
	int maxSum = 0;
	int currentSum;

	for (int i = 0; i < r; i++) {
		for (int j = i; j < r; j++) {
			for (int k = 0; k < c; k++) {
				for (int l = k; l < c; l++) {
					currentSum = sum(matrix, i, k, j, l);
					maxSum = max(currentSum, maxSum);
				}
			}
		}
	}

	return maxSum;
}

int solve_2(int** matrix, int r, int c) {
	int** sumMatrix = alloc(r, c);

	int maxSum = 0;
	maxSum = max(matrix[0][0], maxSum);

	// fill sumMatrix
	// and remember max
	sumMatrix[0][0] = matrix[0][0];
	for (int i = 1; i < r; i++) {
		sumMatrix[i][0] = matrix[i][0] + sumMatrix[i - 1][0];
		maxSum = max(sumMatrix[i][0], maxSum);
	}
	for (int j = 1; j < c; j++) {
		sumMatrix[0][j] = matrix[0][j] + sumMatrix[0][j - 1];
		maxSum = max(sumMatrix[0][j], maxSum);
	}
	for (int i = 1; i < r; i++) {
		for (int j = 1; j < c; j++) {
			sumMatrix[i][j] = matrix[i][j] + sumMatrix[i][j - 1]
			+ sumMatrix[i - 1][j] - sumMatrix[i - 1][j - 1];
			maxSum = max(sumMatrix[i][j], maxSum);
		}
	}

	int currentSum;

	// i = 0
	// j = 0
	// --> max sumMatrix

	// i -> 1+
	// j -> 0+
	for (int k = 1; k < r; k++) {
		for (int j = 0; j < c; j++) {

			bool goOn = true;
			for (int l = j; l < c && goOn; l++) {
				currentSum = sumMatrix[k][l]
				- (j == 0 ? 0 : sumMatrix[k][j - 1]);

				if(currentSum < 0) {
					goOn = false;
				} else {
					maxSum = max(currentSum, maxSum);
				}
			}
		}
	}

	// i -> 0+
	// j -> 1+
	for (int i = 0; i < r; i++) {
		for (int k = i; k < r; k++) {

			bool goOn = true;
			for (int l = 1; l < c && goOn; l++) {
				currentSum = sumMatrix[k][l]
				- (i == 0 ? 0 : sumMatrix[i - 1][l]);
				
				if(currentSum < 0) {
					goOn = false;
				} else {
					maxSum = max(currentSum, maxSum);
				}
			}
		}
	}


	// i -> 1+
	// j -> 1+
	for (int i = 1; i < r; i++) {
		for (int k = i; k < r; k++) {
			for (int j = 1; j < c; j++) {

				bool goOn = true;
				for (int l = j; l < c && goOn; l++) {
					currentSum = sumMatrix[k][l]
					- sumMatrix[i - 1][l]
					- sumMatrix[k][j - 1]
					+ sumMatrix[i - 1][j - 1];

					if(currentSum < 0) {
						goOn = false;
					} else {
						maxSum = max(currentSum, maxSum);
					}
				}
			}
		}
	}

	deleteMatrix(sumMatrix, r);

	return maxSum;
}

int main() {

	// stream input, output
	ifstream in("input.txt");
	ofstream out("output.txt");

	// matrix dimensions
	int r, c;

	// read matrix dimension
	in >> r >> c;

	// read matrix
	int** matrix = readMatrix(in, r, c);

	// debug
	// printMatrix(matrix, r, c);

	int maxSum;

	// v1
	// maxSum = solve_1(matrix, r, c);

	// v2
	maxSum = solve_2(matrix, r, c);

	// cout << "Somma max: " << maxSum << endl;

	// return output
	out << maxSum << endl;

	// dealloca
	deleteMatrix(matrix, r);

	return 0;
}
