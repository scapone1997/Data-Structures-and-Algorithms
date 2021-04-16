/*
 * tester.cpp
 *
 *  Created on: 23 dic 2020
 *      Author: vcapo
 */

#include <iostream>
#include <string.h>
#include "Coda.h"
#include "DCoda.h"
using namespace std;

int main(){

	//Creo una nuova Coda
	Coda<string> C1;
	C1.inCoda("Ciao");
	C1.inCoda("come");
	C1.inCoda("stai");
	C1.inCoda("?");

	//Testo operatore di stampa
	cout << C1;

	//Creo una Double Ended Coda
	DCoda<float> C2;

	//inserisco sul fronte
	C2.inserireFronte(3.47);
	C2.inserireFronte(4.47);
	C2.inserireFronte(5.19);

	cout << C2;

	//inserisco sul retro
	C2.inserireRetro(8.91);
	C2.inserireRetro(1.74);
	C2.inserireRetro(15.76);

	cout << C2;

	//cancella dal fronte e dal retro
	C2.cancellaFronte();
	cout << C2;
	C2.cancellaFronte();
	cout << C2;
	C2.cancellaRetro();
	cout << C2;
	C2.cancellaFronte();
	cout << C2;
	C2.cancellaRetro();
	cout << C2;

	return 0;
}









