#include <iostream>
#include "Lista.h"
using namespace std;

int main(){

/***** Test i metodi della classe Lista  *****/

	//Creo lista L1
	Lista<int> L1;
	L1.inserireLista(1, L1.primoLista());
	L1.inserireLista(2, L1.primoLista());
	L1.inserireLista(3, L1.primoLista());
	L1.inserireLista(4, L1.primoLista());
	cout << L1;

	//Creo lista L2
	Lista<int> L2;
	L2.inserireLista(5, L2.primoLista());
	L2.inserireLista(2, L2.primoLista());
	L2.inserireLista(2, L2.primoLista());
	L2.inserireLista(5, L2.primoLista());
	cout << L1;

	//Testo operatre ==
	cout << "La lista L2 è uguale a L1? " << (L2 == L1) << endl;

	//Testo operatore =
	L2 = L1;
	cout << "L2 = L1: " << L2;

	//Testo metodo inverti()
	L2.inverti();
	cout << "L2 invertita: " << L2;

	//Testo metodo palindroma()
	cout << "L2 è palindroma? " << (L2.palindroma()) << endl;

	//Testo costruttore di copia
	Lista <int> L3(L1);
	cout << "L3: " << L3;


	return 0;
}