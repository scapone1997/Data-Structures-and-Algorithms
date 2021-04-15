/*
 * Pila.h
 *
 *  Created on: 13 dic 2020
 *      Author: vcapo
 */

#ifndef PILA_H_
#define PILA_H_

#include <iostream>
#include "eccezzioni_pila.h"
using namespace std;

template <class T>
class Pila;

template <class T>
class nodo_pila{

    friend class Pila<T>;
    private:
        T valore;
        nodo_pila<T>* succ;
};

template <class T>
class Pila{

    public:
        Pila();
        Pila(const Pila<T>&);
        ~Pila();
        void create();
        bool empty() const;
        T read() const;
        void pop();
        void push(const T&);
        int size() const;

        //altri
        bool exist(const T&) const;

        //Overloading operatori
        friend ostream& operator<<(ostream& os, const Pila<T>& P){
        	P.stampa();
        	return os;
        }

    private:
        void stampa() const;
        nodo_pila<T>* testa;
        int lunghezza;
};

template <class T>
Pila<T>::Pila(){

   create();
}

template <class T>
Pila<T>::Pila(const Pila<T>& P){

   create();
   if(!P.empty())
   {
	   Pila<T> supporto;
	   for(nodo_pila<T>* p = P.testa->succ; p != P.testa; p = p->succ)
		   supporto.push(p->valore);
	   while(!supporto.empty())
	   {
		   T v = supporto.read();
		   supporto.pop();
		   push(v);
	   }
   }
}

template <class T>
Pila<T>::~Pila(){

	while(!empty())
		pop();
	delete testa;
}

template <class T>
void Pila<T>::create(){

    testa = new nodo_pila<T>;
    testa->succ = testa;
    lunghezza = 0;
}


template <class T>
bool Pila<T>::empty() const{

	return (lunghezza == 0);
}

template <class T>
T Pila<T>::read() const{

	if(!empty())
		return testa->succ->valore;
	else
		throw PilaVuota();
}


template <class T>
void Pila<T>::pop() {

	if (!empty())
	{
		nodo_pila<T>* t = new nodo_pila<T>;
		t = testa->succ;
		testa->succ = testa->succ->succ;
		delete t;
		lunghezza--;
	}
	else
		throw PilaVuota();
}

template <class T>
void Pila<T>::push(const T& e){

	nodo_pila<T>* t = new nodo_pila<T>;
	t->valore = e;
	t->succ = testa->succ;
	testa->succ = t;
	lunghezza++;

	/* Esercizio: Pila senza duplicati - modificare l'operatore
	 * inPila per una Pila che non ammette elementi duplicati.*/
	/*
	if(!esiste(e))
	{
		nodo_pila<T>* t = new nodo_pila<T>;
		t->valore = e;
		t->succ = testa->succ;
		testa->succ = t;
		lunghezza++;
	}
	 */
}


template <class T>
int Pila<T>::size() const{

	return lunghezza;
}

template <class T>
bool Pila<T>::exist(const T& v) const{

	bool esito = false;
	for(nodo_pila<T>* p = testa->succ; esito == false && p != testa; p = p->succ)
	{
		if(p->valore == v)
			esito = true;
	}
	return esito;
}

template <class T>
void Pila<T>::stampa() const{

	cout << "[";
	nodo_pila<T>* i = testa;
	while(i->succ != testa){
		cout << i->succ->valore;
		cout <<",";
		i = i->succ;
	}
	cout << "]" << endl;
}

#endif /* PILA_H_ */
