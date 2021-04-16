/*
 * Albero_astratto.h
 *
 *  Created on: 8 dic 2020
 *      Author: vcapo
 */

#ifndef ALBERO_ASTRATTO_H_
#define ALBERO_ASTRATTO_H_

#include <iostream>
#include "Albero_eccezioni.h"
using namespace std;

template <class I, class N>
class Albero_astratto{
	public:
		typedef I tipo;
		typedef N nodo;

		virtual void crea() = 0;
		virtual bool vuoto() const = 0;
		virtual void ins_radice(const tipo&) = 0;
		virtual nodo radice() const = 0;
		virtual nodo padre(nodo) const = 0;
		virtual bool foglia(nodo) const = 0;
		virtual nodo primo_figlio(nodo) const = 0;
		virtual bool ultimo_fratello(nodo) const = 0;
		virtual nodo fratello_succ(nodo) const = 0;
		virtual void cancella_sottoalbero(nodo) = 0;
		virtual void scrivi(nodo, const tipo&) = 0;
		virtual tipo leggi(nodo) const = 0;
		virtual void ins_primo_figlio(nodo, const tipo&) = 0;

		//Funzioni che valgono per tutte le implementazioni
		bool esiste(tipo) const;
		void esiste(nodo, tipo, bool&) const;
		int profondita(nodo);
		int larghezza();
		void larghezza(nodo&, int&, int*);
		void previsita();
		void previsita(nodo); //?
		void invisita();
		void invisita(nodo); //?
		void postvisita();
		void postvisita(nodo); //?

};

template <class I, class N>
bool Albero_astratto<I, N>::esiste(tipo v) const{

	bool esito = false;
	esiste(radice(), v, esito);
	return esito;
}

template <class I, class N>
void Albero_astratto<I, N>::esiste(nodo n, tipo v, bool& esito) const{

	if(leggi(n) == v)
		esito = true;
	if(!foglia(n))
		esiste(primo_figlio(n), v, esito);
	if(!ultimo_fratello(n))
		esiste(fratello_succ(n), v, esito);
}

template <class I, class N>
int Albero_astratto<I, N>::profondita(nodo n){

	Albero_astratto<I,N>::nodo k;
	int max = 0;
	int p;
	if(!foglia(n))
	{
		k = primo_figlio(n);
		while(!ultimo_fratello(k)){
			p = profondita(k);
			if(p > max)
				max = p;
			k = fratello_succ(k);
		}
		p = profondita(k);
		if(p > max)
			max = p;
	}
	return max+1;
}

//Da fare
template <class I, class N>
int Albero_astratto<I, N>::larghezza(){

	return 0;
}

template <class I, class N>
void Albero_astratto<I, N>::larghezza(nodo& k, int& level, int* array){
	array[level]++;
}

template <class I, class N>
void Albero_astratto<I, N>::previsita(){

	if(!vuoto())
		previsita(radice());
}

template <class I, class N>
void Albero_astratto<I, N>::previsita(nodo n){

	cout << leggi(n) << endl;
	if(!foglia(n))
		previsita(primo_figlio(n));
	if(!ultimo_fratello(n))
		previsita(fratello_succ(n));
}

template <class I, class N>
void Albero_astratto<I, N>::invisita(){

	if(!vuoto())
		invisita(radice());
}

template <class I, class N>
void Albero_astratto<I, N>::invisita(nodo n){

	if(!foglia(n))
		invisita(primo_figlio(n));
	cout << leggi(n) << endl;
	if(!ultimo_fratello(n))
		invisita(fratello_succ(n));
}

template <class I, class N>
void Albero_astratto<I, N>::postvisita(){

	if(!vuoto())
		postvisita(radice());
}

template <class I, class N>
void Albero_astratto<I, N>::postvisita(nodo n){

	if(!foglia(n))
		postvisita(primo_figlio(n));
	if(!ultimo_fratello(n))
		postvisita(fratello_succ(n));
	cout << leggi(n) << endl;
}

#endif /* ALBERO_ASTRATTO_H_ */
