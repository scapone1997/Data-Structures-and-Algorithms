/*
 * tester.cpp
 *
 *  Created on: 15 dic 2020
 *      Author: vcapo
 */

#include <iostream>
#include "codap.h"
using namespace std;

bool is_heap(int* V, int n); //Esercizio Laboratorio

int main (){

	//Creo coda con priorità C e inserisco i valori
	CodaP<int> C;
	C.inserisci(15);
	C.inserisci(34);
	C.inserisci(15);
	C.inserisci(29);
	C.inserisci(14);
	C.inserisci(54);
	C.inserisci(74);
	C.inserisci(33);

	//Stampo la coda C
	cout << C << endl;

	int arr[] = {1, 4, 8, 15};
	cout << "Il vettore arr rappresenta un heap? " << is_heap(arr, 4);

	return 0;
}

/*
 * Esercizio di Laboratorio:
 * Scrivere una procedura C++ che, dato un vettore di interi V di n elementi
 * in ingresso, verifichi efficientemente che tale vettore soddisfi la
 * proprietà di heap.
 */
bool is_heap(int* V, int n){

	bool esito = true;
	int k = n;
  	while(k > 1 && esito == true)
  	{
  		if(k % 2 == 0)
  		{
  			if(V[k-1] < V[k/2-1])
  				esito = false;
  		}
  		else
  		{
  			if(V[k-1] < V[k/2-1])
  				esito = false;
  		}
  		k = k-1;
    }
	return esito;
}













