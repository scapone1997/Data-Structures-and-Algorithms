/*
 * DCoda.h
 *
 *  Created on: 23 dic 2020
 *      Author: vcapo
 */

#ifndef DCODA_H_
#define DCODA_H_

#include <iostream>
#include "eccezioni_coda.h"
using namespace std;

template <class T>
class DCoda;

template <class T>
class Nodo{

    friend class DCoda<T>;
    private:
        T valore;
        Nodo<T>* fronte;
        Nodo<T>* retro;
};

template <class T>
class DCoda{

    public:
		DCoda();
		~DCoda();

		void creaCoda();
		void inserireFronte(const T&);
		void inserireRetro(const T&);
		void cancellaFronte();
		void cancellaRetro();
		T leggiFronte() const;
		T leggiRetro() const;
		bool codaVuota() const;
		bool esiste(const T&) const;
		int dimensione() const;

		//Overloading operatori
		DCoda<T>& operator=(const DCoda<T>& altra);
		friend ostream& operator<<(ostream& os, const DCoda<T>& A){
			A.stampa();
			return os;
		}

    private:
		void stampa() const;
        Nodo<T>* testa;
        int lunghezza;
};

template <class T>
DCoda<T>::DCoda(){

	creaCoda();
}

template <class T>
DCoda<T>::~DCoda(){

	while(!codaVuota())
		cancellaFronte();
	delete testa;
}

template <class T>
void DCoda<T>::creaCoda(){

	testa = new Nodo<T>;
	testa->fronte = testa;
	testa->retro = testa;
	lunghezza = 0;
}

template <class T>
void DCoda<T>::inserireFronte(const T& nuovo){

	Nodo<T>* nodo = new Nodo<T>;
	nodo->valore = nuovo;
	if(lunghezza == 0)
	{
		nodo->fronte = testa;
		nodo->retro = testa;
		testa->fronte = nodo;
		testa->retro = nodo;
	}
	else
	{
		nodo->fronte = testa->fronte;
		nodo->retro = testa;
		testa->fronte->retro = nodo;
		testa->fronte = nodo;
	}
	lunghezza++;
}

template <class T>
void DCoda<T>::inserireRetro(const T& nuovo){

	Nodo<T>* nodo = new Nodo<T>;
	nodo->valore = nuovo;

	if(lunghezza == 0)
	{
		nodo->fronte = testa;
		nodo->retro = testa;
		testa->fronte = nodo;
		testa->retro = nodo;
	}
	else
	{
		nodo->retro = testa->retro;
		nodo->fronte = testa;
		testa->retro->fronte = nodo;
		testa->retro = nodo;
	}
	lunghezza++;
}

template <class T>
void DCoda<T>::cancellaFronte(){

	if(!codaVuota())
	{
		Nodo<T>* t = new Nodo<T>;
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
void DCoda<T>::cancellaRetro(){

	if(!codaVuota())
	{
		Nodo<T>* t = new Nodo<T>;
		if(lunghezza == 1)
		{
			t = testa->retro;
			delete t;
			testa->retro = testa;
			testa->fronte = testa;
			lunghezza--;
		}
		else
		{
			t = testa->retro;
			testa->retro->retro->fronte = testa;
			testa->retro = testa->retro->retro;
			delete t;
			lunghezza--;
		}
	}
}

template <class T>
T DCoda<T>::leggiFronte() const{

	if(!codaVuota())
		return testa->fronte->valore;
	else
		throw CodaVuota();
}

template <class T>
T DCoda<T>::leggiRetro() const{

	if(!codaVuota())
		return testa->retro->valore;
	else
		throw CodaVuota();
}

template <class T>
bool DCoda<T>::codaVuota() const{

	return (lunghezza == 0);
}

template <class T>
bool DCoda<T>::esiste(const T& e) const{

	bool esito = false;
	if(!codaVuota())
	{
		Nodo<T>* t = new Nodo<T>;
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
int DCoda<T>::dimensione() const{

	return lunghezza;
}

template <class T>
void DCoda<T>::stampa() const{

	cout << "[" << lunghezza;
	cout << "]: [";
	if(!codaVuota())
	{
		Nodo<T>* t = new Nodo<T>;
		t = testa->fronte;
		while(t != this->testa)
		{
			cout << t->valore << " ";
			t = t->fronte;
		}
	}
	cout << "]" << endl << endl;
}

					/********** Overloading operatori **********/
template<class T>
DCoda<T>& DCoda<T>::operator=(const DCoda& A){

	if (this != &A)
	{
		this->~DCoda();
		creaCoda();
		if (!A.codaVuota())
		{
			Nodo<T>* t = new Nodo<T>;
			t = A.testa->fronte;
			while(t != A.testa)
			{
				inserireRetro(t->valore);
				t = t->fronte;
			}
		}
	}
	return *this;
}

#endif /* DCODA_H_ */
