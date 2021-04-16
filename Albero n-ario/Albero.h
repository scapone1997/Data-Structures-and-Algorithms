/*
 * Albero.h
 *
 *  Created on: 10 dic 2020
 *      Author: vcapo
 */

#ifndef ALBERO_H_
#define ALBERO_H_

#include <iostream>
#include "Albero_astratto.h"
using namespace std;

template <class I>
class Albero;

template <class I>
class cella{

	friend class Albero<I>;
	private:
		I valore;
		cella<I>* padre;
		cella<I>* fratello;
		cella<I>* primo_figlio;
};


template <class I>
class Albero : public Albero_astratto<I, cella<I>*>{

	public:
		typedef typename Albero_astratto<I, cella<I>*>::tipo tipo;
		typedef typename Albero_astratto<I, cella<I>*>::nodo nodo;

		Albero();
		Albero(const Albero<I>&);
		~Albero();

		//Metodi principali
		void crea();
		bool vuoto() const;
		void ins_radice(const tipo&);
		nodo radice() const;
		nodo padre(nodo) const;
		bool foglia(nodo) const;
		nodo primo_figlio(nodo) const;
		bool ultimo_fratello(nodo) const;
		nodo fratello_succ(nodo) const;
		void cancella_sottoalbero(nodo); //da fare
		void scrivi(nodo, const tipo&);
		tipo leggi(nodo) const;
		void ins_primo_figlio(nodo, const tipo&);

		//altri
		void ins_fratello(nodo, const tipo&);
		void ins_primo_sottoalbero(nodo, const Albero<I>&); //inserisce il nuovo albero come primo figlio del nodo passato come parametro
		void ins_sottoalbero(nodo, const Albero<I>&);//inserisce il nuovo albero come fratello del nodo passato come parametro

	private:
		nodo copia_sottoalbero(nodo n, nodo g);
		cella<I>* inizio;
};


template <class I>
Albero<I>::Albero(){

	crea();
}


template <class I>
Albero<I>::Albero(const Albero<I>& A){

	if(!A.vuoto())
		inizio = copia_sottoalbero(A.radice(), nullptr);
	else
		crea();
}


template <class I>
Albero<I>::~Albero(){

	cancella_sottoalbero(radice());
	delete inizio;
}


template <class I>
void Albero<I>::crea(){

	inizio = nullptr;
}


template <class I>
bool Albero<I>::vuoto() const{

	return (inizio == nullptr);
}


template <class I>
void Albero<I>::ins_radice(const tipo& e){

	if(vuoto())
	{
		inizio = new cella<I>;
		inizio->valore = e;
		inizio->padre = nullptr;
		inizio->fratello = nullptr;
		inizio->primo_figlio = nullptr;
	}
	else
		throw RadiceEsiste();
}


template <class I>
typename Albero<I>::nodo Albero<I>::radice() const{

	if(!vuoto())
		return inizio;
	else
		throw AlberoVuoto();
}


template <class I>
typename Albero<I>::nodo Albero<I>::padre(nodo n) const{

	if(n != radice())
	{
		if(n != nullptr)
			return n->padre;
		else
			throw NodoNullo();
	}
	else
		throw RadiceNonHaPadre();
}


template <class I>
bool Albero<I>::foglia(nodo n) const{

	return (n->primo_figlio == nullptr);
}


template <class I>
typename Albero<I>::nodo Albero<I>::primo_figlio(nodo n) const{

	if(!foglia(n))
		return n->primo_figlio;
	else
		throw QuestoNodoNonHaFigli();
}


template <class I>
bool Albero<I>::ultimo_fratello(nodo n) const{

	return (n->fratello == nullptr);
}


template <class I>
typename Albero<I>::nodo Albero<I>::fratello_succ(nodo n) const{

	if(!ultimo_fratello(n))
		return n->fratello;
	else
		throw QuestoNodoNonHaFratelli();
}


template <class I>
void Albero<I>::cancella_sottoalbero(nodo n){

	if(n != nullptr)
	{
		if(n == inizio)
		{
			while(!foglia(n))
				cancella_sottoalbero(n->primo_figlio);
			inizio = nullptr;
		}
		else
		{
			while(!foglia(n))
				cancella_sottoalbero(n->primo_figlio);
			if(n->padre->primo_figlio == n)
			{
				if(ultimo_fratello(n))
					n->padre->primo_figlio = nullptr;
				else
					n->padre->primo_figlio = n->fratello;
				delete n;
			}
			else
			{
				cella<I>* t = n->padre->primo_figlio;
				while(fratello_succ(t) != n){
					t = t->fratello;
				}
				t->fratello = n->fratello;
				delete n;
			}
		}
	}
}


template <class I>
void Albero<I>::scrivi(nodo n, const tipo& e){

	n->valore = e;
}


template <class I>
typename Albero<I>::tipo Albero<I>::leggi(nodo n) const{

	return n->valore;
}


template <class I>
void Albero<I>::ins_primo_figlio(nodo n, const tipo& e){

	if(!vuoto())
	{
		if(n != nullptr)
		{
			if(foglia(n))
			{
				n->primo_figlio = new cella<I>;
				n->primo_figlio->valore = e;
				n->primo_figlio->fratello = nullptr;
				n->primo_figlio->primo_figlio = nullptr;
				n->primo_figlio->padre = n;
			}
			else
			{
				cella<I>* t = new cella<I>;
				t->valore = e;
				t->fratello = n->primo_figlio;
				t->primo_figlio = nullptr;
				t->padre = n;
				n->primo_figlio = t;
			}
		}
		else
			throw NodoNullo();
	}
	else
		throw AlberoVuoto();
}


template <class I>
void Albero<I>::ins_fratello(nodo n, const tipo& e){

	if(!vuoto())
	{
		if(n != nullptr)
		{
			if(n != inizio)
			{
				cella<I>* t = new cella<I>;
				t->valore = e;
				t->padre = n->padre;
				t->primo_figlio = nullptr;
				if(ultimo_fratello(n))
				{
					t->fratello = nullptr;
					n->fratello = t;
				}
				else
				{
					t->fratello = n->fratello;
					n->fratello = t;
				}
			}
			else
				throw RadiceNonHaFratelli();
		}
		else
			throw NodoNullo();
	}
	else
		throw AlberoVuoto();
}


template <class I>
void Albero<I>::ins_primo_sottoalbero(nodo n, const Albero<I>& A){

	if(!A.vuoto())
	{
		if(n != nullptr)
		{
			cella<I>* a = copia_sottoalbero(A.radice(), nullptr);
			a->fratello = n->primo_figlio;
			a->padre = n;
			n->primo_figlio = a;
		}
		else
			throw NodoNullo();
	}
}


template <class I>
void Albero<I>::ins_sottoalbero(nodo n, const Albero<I>& A){

	if(!A.vuoto())
	{
		if(n != nullptr)
		{
			if(n != inizio)
			{
				cella<I>* a = copia_sottoalbero(A.radice(), nullptr);
				a->padre = n->padre;
				if(ultimo_fratello(n))
				{
					a->fratello = nullptr;
					n->fratello = a;
				}
				else
				{
					a->fratello = n->fratello;
					n->fratello = a;
				}
			}
			else
				throw RadiceNonHaFratelli();
		}
		else
			throw NodoNullo();
	}
}


template <class I>
typename Albero<I>::nodo Albero<I>::copia_sottoalbero(nodo n, nodo g){

	if(n != nullptr)
	{
		cella<I>* nuovo = new cella<I>;
		nuovo->valore = n->valore;
		nuovo->padre = g;
		nuovo->fratello = copia_sottoalbero(n->fratello, g);
		nuovo->primo_figlio = copia_sottoalbero(n->primo_figlio, nuovo);
		return nuovo;
	}
	else
		return nullptr;
}


#endif /* ALBERO_H_ */
