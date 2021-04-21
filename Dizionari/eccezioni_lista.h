/*
 * eccezioni_lista.h
 *
 *  Created on: 5 dic 2020
 *      Author: vcapo
 */

#ifndef ECCEZIONI_LISTA_H_
#define ECCEZIONI_LISTA_H_

#include <iostream>
#include <string>
using namespace std;

class eccezioni_lista{
	public:
		eccezioni_lista () : message("List Exception") {};
		eccezioni_lista (string customMessage) { message = customMessage; };
		void printMessage () { std::cout << message << std::endl; };
	private:
		string message;
};

class ListaVuota : public eccezioni_lista{
	public:
		ListaVuota() : eccezioni_lista("Eccezione lista vuota") {};
};

class ListaPiena : public eccezioni_lista{
	public:
		ListaPiena() : eccezioni_lista("Eccezione lista piena") {};
};

class PosizioneNonValida : public eccezioni_lista{
	public:
		PosizioneNonValida() : eccezioni_lista("Index Out Of Range List Exception") {};
};


#endif /* ECCEZIONI_LISTA_H_ */
