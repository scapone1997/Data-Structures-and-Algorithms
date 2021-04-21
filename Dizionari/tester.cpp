/*
 * tester.cpp
 *
 *  Created on: 16 gen 2021
 *      Author: vcapo
 */

#include <iostream>
#include "Dictionary.h"

int main(){

	Dictionary<int, string> D(5);
	D.inserisci(1, "Simone");
	D.inserisci(0, "Naomi");
	D.inserisci(3, "Lisa");
	D.inserisci(4, "Marco");
	D.cancella(1);
	cout << D;
	cout << D.keys();
	cout << D.values();

	system("PAUSE");
	return 0;
}
