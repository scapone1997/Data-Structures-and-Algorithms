/*
 * MultipleStack.h
 *
 *  Created on: 13 dic 2020
 *      Author: vcapo
 */

#ifndef MULTIPLESTACK_H_
#define MULTIPLESTACK_H_

#include "Pila.h"

template <class T>
class MultipleStack {

	public:
		MultipleStack(unsigned int n);
		~MultipleStack();
		void inserisci(T& elemento, unsigned int);
		void cancella(unsigned int);
		T leggiTesta(unsigned int p) const;

        friend ostream& operator<<(ostream& os, const MultipleStack<T>& MS){
        	for(int i = 0; i < MS.dimensione; i++){
        		os << MS.array[i];
        	}
        	return os;
        }

	private:
		Pila<T>* array;
		int dimensione;
};


template <class T>
MultipleStack<T>::MultipleStack(unsigned int n){

	array = new Pila<T>[n];
	dimensione = n;

}


//corretto dal forum
template <class T>
MultipleStack<T>::~MultipleStack(){

	if(array != 0)
	{
	    delete[] array;
	    array = 0;
	}
	return;
}


template <class T>
void MultipleStack<T>::inserisci(T& elemento, unsigned int p){

	if(p < (unsigned)dimensione)
		array[p].inPila(elemento);
	else cout << "Non esiste questa posizione!";

}


template <class T>
void MultipleStack<T>::cancella(unsigned int p){

	if(p < (unsigned)dimensione)
		array[p].fuoriPila();
	else cout << "Non esiste questa posizione!";

}


template <class T>
T MultipleStack<T>::leggiTesta(unsigned int p) const {

	T elemento;
	elemento = array[p].leggiPila();

	return elemento;

}

#endif /* MULTIPLESTACK_H_ */
