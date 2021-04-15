/*
 * tester.cpp
 *
 *  Created on: 13 dic 2020
 *      Author: vcapo
 */


#include <iostream>
#include "MultipleStack.h"
#include "Pila.h"

using namespace std;

int main(){

    //Creo la pila P1
    Pila<int> P1;

    //Riempio la pila
    P1.push(3);
    P1.push(4);
    P1.push(5);
    P1.push(6);
    P1.push(11);

    //Testo operatore <<
    cout << "P1: " << P1;

    //Creo la pila P2 con il secondo costruttore
    Pila<int> P2(P1);
    cout << "P2: " << P2;

    //Testo operatore esiste
    cout << "esiste elemento 5 in P2? " << (P2.exist(5)) << endl;

    //elimino elemento
    P2.pop();
    cout << "P2: " << P2;

    //testo metodo empty
    cout << "P2 è vuota? " << (P2.empty()) << endl;

    return 0;
}
