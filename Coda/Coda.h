/*
 * Coda.h
 *
 *  Created on: 23 dic 2020
 *      Author: vcapo
 */

#ifndef CODA_H_
#define CODA_H_

#include <iostream>
#include "eccezioni_coda.h"
using namespace std;

template <class T>
class Coda;

template <class T>
class nodo{

	friend class Coda<T>;
    private:
        T valore;
        nodo<T>* fronte;
        nodo<T>* retro;
};

template <class T>
class Coda{

	public:
		Coda();
		Coda(const Coda<T>&);
		~Coda();
		void creaCoda();
		bool codaVuota() const;
		void inCoda(const T&);
		void fuoriCoda();
		T leggiCoda() const;
		int dimensione() const;
		bool esiste(const T&) const;

		//Overloading operatori
		Coda<T>& operator=(const Coda<T>& altra);
		bool operator==(const Coda<T>& altra);
		friend ostream& operator<<(ostream& os, const Coda<T>& A){
			A.stampa();
			return os;
		}

	private:
		void stampa() const;
        nodo<T>* testa;
        int lunghezza;
};

template <class T>
Coda<T>::Coda(){

	creaCoda();
}

template <class T>
Coda<T>::Coda(const Coda<T>& C){

	creaCoda();
	if(!C.codaVuota())
	{
		nodo<T>* t = new nodo<T>;
		t = C.testa->fronte;
		while(t != C.testa)
		{
			this->inCoda(t->valore);
			t = t->fronte;
		}
	}
}

template <class T>
Coda<T>::~Coda(){

	while(!codaVuota())
		fuoriCoda();
	delete testa;
}

template <class T>
void Coda<T>::creaCoda(){

	testa = new nodo<T>;
	testa->fronte = testa;
	testa->retro = testa;
	lunghezza = 0;
}

template <class T>
bool Coda<T>::codaVuota() const{

	return (lunghezza == 0);
}

template <class T>
void Coda<T>::fuoriCoda(){

	if(!codaVuota())
	{
		nodo<T>* t = new nodo<T>;
		if(lunghezza == 1)
		{
			t = testa->fronte;
			delete t;
			testa->fronte = testa;
			testa->retro = testa;
			lunghezza--;
		}
		else
		{
			t = testa->fronte;
			testa->fronte = testa->fronte->fronte;
			testa->fronte->retro = testa;
			delete t;
			lunghezza--;
		}
	}
}

template <class T>
void Coda<T>::inCoda(const T& e){

	nodo<T>* t = new nodo<T>;
	t->valore = e;

	if(lunghezza == 0)
	{
		t->fronte = testa;
		t->retro = testa;
		testa->fronte = t;
		testa->retro = t;
	}
	else
	{
		t->retro = testa->retro;
		t->fronte = testa;
		testa->retro->fronte = t;
		testa->retro = t;
	}
	lunghezza++;
}

template <class T>
T Coda<T>::leggiCoda() const{

	if(!codaVuota())
		return testa->fronte->valore;
	else
		throw CodaVuota();
}

template <class T>
int Coda<T>::dimensione() const{

	return lunghezza;
}

template <class T>
bool Coda<T>::esiste(const T& e) const{

	bool esito = false;
	if(!this->codaVuota())
	{
		nodo<T>* t = new nodo<T>;
		t = testa->fronte;
		while(t != testa && esito == false)
		{
			if(t->valore == e)
				esito = true;
			t = t->fronte;
		}
	}
	return esito;
}

template <class T>
void Coda<T>::stampa() const{

	cout << "[" << lunghezza;
	cout << "]: [";
	if(!codaVuota())
	{
		nodo<T>* t = new nodo<T>;
		t = testa->fronte;
		while(t != this->testa)
		{
			cout << t->valore << ", ";
			t = t->fronte;
		}
	}
	cout << "]" << endl << endl;
}

template<class T>
Coda<T>& Coda<T>::operator=(const Coda& A){

	if (this != &A)
	{
		this->~Coda();
		creaCoda();
		if (!A.codaVuota())
		{
			nodo<T>* t = new nodo<T>;
			t = A.testa->fronte;
			while(t != A.testa)
			{
				inCoda(t->valore);
				t = t->fronte;
			}
		}
	}
	return *this;
}

template<class T>
bool Coda<T>::operator==(const Coda& A){

	bool esito = true;
	if (this != &A)
	{
		if (A.dimensione() == this->dimensione())
		{
			nodo<T>* a = new nodo<T>;
			nodo<T>* t = new nodo<T>;
			a = A.testa->fronte;
			t = this->testa->fronte;
			while(a != A.testa && esito == true)
			{
				if(a->valore != t->valore)
					esito = false;
				a = a->fronte;
				t = t->fronte;
			}
		}
		else
			esito = false;
	}
	return esito;
}


#endif /* CODA_H_ */
