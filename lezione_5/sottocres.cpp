//============================================================================
// Name        : sottocres.cpp
// Author      : Davide Pedranz
// Version     : 1
// Licence     : GPL v2
// Description : Programmazione dinamica - sottoinsieme crescente somma max
//============================================================================

#include <fstream>
#include <algorithm>
using namespace std;

const int VOID = -1;

int sottocres(int i, int* a, int* D) {

    if (D[i] == VOID) {
        int max = 0;
        for (int k = 0; k < i; k++) {
            int res = sottocres(k, a, D);
            if (a[k] <= a[i] && res > max) {
                max = res;
            }
        }
        D[i] = max + a[i];
    }

    return D[i];
}


int sottocres(int* a, int n) {

	int* D = new int[n];
	fill(D, D+n, VOID);

    // riempio tutto l'array per la programmazione dimanica
    // nella casella i-esesima è scritta la soluzione per 
    // il sottoproblema ristretto ai primi i elementi
    sottocres(n-1, a, D);

    // il risultato è il massimo contenuto nell'array
    int result = *max_element(D, D+n);

    delete[] D;
    return result;
}


int main() {

   ifstream in("input.txt");
   ofstream out("output.txt");

   int n;
   in >> n;

   int* a = new int[n];

   for(int i = 0; i < n; i++) {
      in >> a[i];
  }

  int result = sottocres(a, n);
  out << result << endl;

  delete[] a;
  in.close();
  out.close();

  return 0;
}