/*
 * tester.cpp
 *
 *  Created on: 25 nov 2020
 *      Author: vcapo
 */

#include <iostream>
#include "Albero_binario_p.h"
#include "Albero_binario_v.h"

int main(){
			/************* Test albero binario puntatori ****************/

	//Creo albero binario P
	cout << "Albero con puntatori: " << endl;
	Albero_binario_p<int> P;
	cella<int>* c = new cella<int>;

	//Riempio P
	P.inserire_radice(c);
	P.scrivi(P.radice(), 1);
	cout << "P: ";
	cout << P << endl;

	//Creo albero binario G
	Albero_binario_p<int> G;
	cella<int>* c1 = new cella<int>;

	//Riempio G
	G.inserire_radice(c1);
	G.scrivi(G.radice(), 1);
	G.inserire_destro(G.radice());
	G.inserire_sinistro(G.radice());
	G.scrivi(G.sinistro(G.radice()), 12);
	G.scrivi(G.destro(G.radice()), 4);
	G.inserire_destro(G.sinistro(G.radice()));
	G.inserire_sinistro(G.sinistro(G.radice()));
	G.scrivi(G.sinistro(G.sinistro(G.radice())), 174);
	G.scrivi(G.destro(G.sinistro(G.radice())), 203);
	G.inserire_destro(G.destro(G.radice()));
	G.inserire_sinistro(G.destro(G.radice()));
	G.scrivi(G.sinistro(G.destro(G.radice())), 0);
	G.scrivi(G.destro(G.destro(G.radice())), -3);
	G.inserire_destro(G.destro(G.destro(G.radice())));
	G.scrivi(G.destro(G.destro(G.destro(G.radice()))), 15);
	cout << "G: ";
	cout << G << endl;

	//Testo operatore =
	P = G;
	cout << "P: ";
	cout << P << endl;

	//Testo Operatore ==
	cout << "P == G? " << (P == G) << endl;

	//Testo profondita
	cout << "Altezza: " << G.altezza(G.radice()) << endl;
	cout << "Esiste: " << (G.esiste(15)) << endl;
	cout << "Larghezza: " << G.larghezza() << endl;

	return 0;
}
