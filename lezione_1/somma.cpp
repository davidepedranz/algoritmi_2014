//============================================================================
// Name        : somma.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Lab_1, Task_0: somma
//============================================================================

#include <fstream>
using namespace std;

int main() {

	ifstream in("input.txt");
	ofstream out("output.txt");

	int a, b;
	in >> a >> b;
	out << a + b << "\n";

	return 0;
}