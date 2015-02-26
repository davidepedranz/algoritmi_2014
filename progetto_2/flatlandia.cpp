//============================================================================
// Author      : Luca Bosotti, Marco Federici, Davide Pedranz
// Licence     : GPL v2
//============================================================================

#include <fstream>
using namespace std;

int main() {
	ifstream in("input.txt");
	ofstream out("output.txt");

	int num;
	in >> num;

	string s;
	in >> s;

	int size = (num-1)/2 + 1;

	int* risultati = new int[size];
	int index = 0;

	bool* plausibili = new bool[size];

	for(int i = 0; i < size; i++) {
		plausibili[i] = true;
	}

	for (int i = 1; i < num; i+=2) {
		if(s[i] == 'd') {
			plausibili[(i+1)/2] = false;
		} else if(s[i+1]=='d') {
			break;
		}
	}
	for (int i = num-2; i >= 0; i-=2) {
		if(s[i]=='s') {
			plausibili[(i-1)/2] = false;
		} else if(s[i-1]=='s') {
			break;
		}
	}
	
	for(int i = 0; i < size; i++) {
		if(plausibili[i]) {
			risultati[index++] = i*2;
		}
	}

	out << index << endl;
	for (int i = 0; i < index; i++) {
		out << risultati[i] << " ";
	}
	out << endl;

	in.close();
	out.close();

	delete[] risultati;
	delete[] plausibili;
	return 0;
}
