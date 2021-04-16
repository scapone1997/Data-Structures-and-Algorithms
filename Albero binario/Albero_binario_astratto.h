/*
 * Albero_binario.h
 *
 *  Created on: 25 nov 2020
 *      Author: vcapo
 */

#ifndef ALBERO_BINARIO_ASTRATTO_H_
#define ALBERO_BINARIO_ASTRATTO_H_

#include <iostream>
#include <vector>
#include "alberobinario_eccezioni.h"
using namespace std;


template <class T, class N>
class Albero_binario_astratto{

	public:
		typedef T tipo;
		typedef N Nodo;

		//Operatori
		virtual void crea() = 0;
		virtual bool vuoto() const = 0;
		virtual Nodo radice() const = 0;
		virtual Nodo genitore(Nodo) const = 0;
		virtual Nodo sinistro(Nodo) const = 0;
		virtual Nodo destro(Nodo) const = 0;
		virtual bool sinistro_vuoto(Nodo) const = 0;
		virtual bool destro_vuoto(Nodo) const = 0;
		virtual void cancella(Nodo) = 0;
		virtual tipo leggi(Nodo) const = 0;
		virtual void scrivi(Nodo, tipo) = 0;
		virtual void inserire_radice(Nodo) = 0;
		virtual void inserire_sinistro(Nodo) = 0;
		virtual void inserire_destro(Nodo) = 0;

		//Metodi chiamabili da tutte le implementazioni
		int altezza(Nodo);
		int larghezza();
		void larghezza(Nodo, unsigned int, vector<int>&);
		bool esiste(tipo) const;
		void esiste(Nodo, tipo, bool&) const;
		void previsita();
		void previsita(Nodo);
		void invisita();
		void invisita(Nodo);
		void postvisita();
		void postvisita(Nodo);
		void cancella_foglie_pari();
		void cancella_foglie_pari(Nodo);
		void stampa() const;

		//Overoloading operatori
		//operator <<

	private:
		virtual void stampa_sottoalbero(const Nodo) const;
};

template <class T, class N>
int Albero_binario_astratto<T, N>::altezza(Nodo n){

	int s = 0;
	int d = 0;
	int max = 0;
	if(!sinistro_vuoto(n))
		s = altezza(sinistro(n));
	if(!destro_vuoto(n))
		d = altezza(destro(n));
	if(s >= d)
		max = s;
	else
		max = d;
	return max+1;
}

template <class T, class N>
int Albero_binario_astratto<T, N>::larghezza(){

	vector<int> S;
	larghezza(radice(), 1, S);
	int max = S[0];
	int pos_max = 0;
	for(unsigned int i = 1; i<S.size(); i++)
		if(S[i] > max)
			max = S[i];
	return max;
}

template <class T, class N>
void Albero_binario_astratto<T, N>::larghezza(Nodo n, unsigned int d, vector<int>& S){

	if(S.size() < d)
		S.push_back(0);
	S[d-1]++;
	if(!sinistro_vuoto(n))
		larghezza(sinistro(n), d+1, S);
	if(!destro_vuoto(n))
		larghezza(destro(n), d+1, S);
}

template <class T, class N>
bool Albero_binario_astratto<T, N>::esiste(tipo e) const{

	bool esito = false;
	esiste(radice(), e, esito);
	return esito;
}

template <class T, class N>
void Albero_binario_astratto<T, N>::esiste(Nodo n, tipo e, bool& esito) const{

	if(leggi(n) == e)
		esito = true;
	if(!sinistro_vuoto(n))
		esiste(sinistro(n), e, esito);
	if(!destro_vuoto(n))
		esiste(destro(n), e, esito);
}

template <class T, class N>
void Albero_binario_astratto<T, N>::previsita(){

	if(!vuoto())
		previsita(radice());
}

template <class T, class N>
void Albero_binario_astratto<T, N>::previsita(Nodo n){

	cout << leggi(n) << endl;
	if(!sinistro_vuoto(n))
		previsita(sinistro(n));
	if(!destro_vuoto(n))
		previsita(destro(n));
}

template <class T, class N>
void Albero_binario_astratto<T, N>::invisita(){

	if(!vuoto())
		invisita(radice());
}

template <class T, class N>
void Albero_binario_astratto<T, N>::invisita(Nodo n){

	if(!sinistro_vuoto(n))
		invisita(sinistro(n));
	cout << leggi(n) << endl;
	if(!destro_vuoto(n))
		invisita(destro(n));
}

template <class T, class N>
void Albero_binario_astratto<T, N>::postvisita(){

	if(!vuoto())
		postvisita(radice());
}

template <class T, class N>
void Albero_binario_astratto<T, N>::postvisita(Nodo n){

	if(!sinistro_vuoto(n))
		postvisita(sinistro(n));
	if(!destro_vuoto(n))
		postvisita(destro(n));
	cout << leggi(n) << endl;
}

template <class T, class N>
void Albero_binario_astratto<T, N>::cancella_foglie_pari(){

	if(!vuoto())
		cancella_foglie_pari(radice());
}

template <class T, class N>
void Albero_binario_astratto<T, N>::cancella_foglie_pari(Nodo n){

	if(!sinistro_vuoto(n))
		cancella_foglie_pari(sinistro(n));

	//visita
	if(leggi(n) % 2 == 0 && sinistro_vuoto(n) && destro_vuoto(n))
		cancella(n);
	if(!destro_vuoto(n))
		cancella_foglie_pari(destro(n));
}

template <class T, class N>
void Albero_binario_astratto<T, N>::stampa() const{

	if (!vuoto())
		stampa_sottoalbero(radice());
	else
		cout << "[]" << endl;

	cout << endl;
}

template <class T, class N>
void Albero_binario_astratto<T, N>::stampa_sottoalbero(const Nodo n) const{

	cout << "[" << leggi(n) << ", ";
	if (!sinistro_vuoto(n))
		stampa_sottoalbero(sinistro(n));
	else cout << "NIL";
	cout << ", ";

	if (!destro_vuoto(n))
		stampa_sottoalbero(destro(n));
	else cout << "NIL";
	cout << " ]";
}

/********************* Overloading operatori ****************************/
template<class T, class N>
ostream& operator<<(std::ostream& os, const Albero_binario_astratto<T, N>& t) {

	t.stampa();
    return os;
}

#endif /* ALBERO_BINARIO_ASTRATTO_H_ */
