/*
 * tester.cpp
 *
 *  Created on: 10 dic 2020
 *      Author: vcapo
 */

#include <iostream>
#include "Albero.h"
using namespace std;

int main(){

	//Creo albero n-ario A
	Albero<int> A;
	A.ins_radice(9);
	A.ins_primo_figlio(A.radice(), 18);
	A.ins_primo_figlio(A.radice(), 33);
	A.ins_fratello(A.primo_figlio(A.radice()), 57);
	A.ins_fratello(A.primo_figlio(A.radice()), 72);

	//Creo albero n-ario B
	Albero<int> B;
	B.ins_radice(154);
	B.ins_primo_figlio(B.radice(), 354);
	B.ins_fratello(B.primo_figlio(B.radice()), 455);
	A.ins_sottoalbero(A.primo_figlio(A.radice()), B);

	//Calcolo la profondita dell'albero
	cout << "Profondita' A: " << A.profondita(A.radice()) << endl;

	//Visito l'albero per verificare l'esistenza di un numero attraverso il metodo esiste()
	cout << "Esiste il numero 57 nell'albero A? " << (A.esiste(57)) << endl;

	//Appendo l'albero B alla radice di A
	A.ins_sottoalbero(A.radice(), B);

	return 0;
}
