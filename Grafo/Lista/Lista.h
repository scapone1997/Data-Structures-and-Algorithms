/*
 * LinkedList.h
 *
 *  Created on: 4 nov 2020
 *      Author: vcapo
 */

#ifndef LISTA_H_
#define LISTA_H_

#include "LinearList.h"
#include "eccezioni_lista.h"

template<class T>
class Lista;

template<class T>
class ListaOrdinata;


template<class T>
class ListNode{
	friend class Lista<T>;
	friend class ListaOrdinata<T>;

	private:
		T valore;
		ListNode<T>* prec;
		ListNode<T>* succ;
};


template<class T>
class Lista : public LinearList<T, ListNode<T>*>{

	public:
		typedef typename LinearList<T, ListNode<T>*>::tipo tipo;
		typedef typename LinearList<T, ListNode<T>*>::posizione posizione;

		Lista();
		Lista(const Lista<T>& altraLista);
		~Lista();

		void creaLista();
		bool listaVuota() const;
		tipo leggiLista(posizione) const;
		void scriviLista(const tipo&, posizione);
		posizione primoLista() const;
		bool fineLista(posizione) const;
		posizione successivo(posizione) const;
		posizione precedente(posizione) const;
		void inserireLista(const tipo&, posizione);
		void cancellaLista(posizione);
		posizione ultimoLista() const;

		//Overloading operatori
		Lista<T>& operator=(const Lista<T>&);

	private:
		ListNode<T>* testa;
		int lunghezza;
};


template<class T>
Lista<T>::Lista(){

	creaLista();
}


template<class T>
Lista<T>::Lista(const Lista<T>& L) {

	creaLista();
	if (!L.listaVuota())
	{
		posizione p = L.ultimoLista();
		for(posizione p = L.primoLista(); !L.fineLista(p); p = L.successivo(p)){
			inserireLista(L.leggiLista(p), ultimoLista());
		}
	}
}


template<class T>
Lista<T>::~Lista(){

	while(!listaVuota())
		cancellaLista(primoLista());
	delete testa;
}


template<class T>
void Lista<T>::creaLista(){

	 testa = new ListNode<T>;
	 testa->succ = testa;
	 testa->prec = testa;
	 lunghezza = 0;
}


template<class T>
bool Lista<T>::listaVuota() const{

	return(testa->succ == testa);
}



template<class T>
typename Lista<T>::posizione Lista<T>::primoLista() const{

	return (testa->succ);
}


template<class T>
typename Lista<T>::posizione Lista<T>::ultimoLista() const{

	return (testa->prec);
}


template<class T>
typename Lista<T>::posizione Lista<T>::successivo(posizione p) const{

	return(p->succ);
}


template<class T>
typename Lista<T>::posizione Lista<T>::precedente(posizione p) const{

	return(p->prec);
}


template<class T>
bool Lista<T>::fineLista(posizione p) const{

	return(p == testa);
}


template<class T>
typename Lista<T>::tipo Lista<T>::leggiLista(posizione p) const {

	if (!listaVuota())
		return(p->valore);
	else
		throw ListaVuota();
}


template<class T>
void Lista<T>::scriviLista(const tipo &valore, posizione p) {

	if (!listaVuota())
		p->valore = valore;
	else
		throw ListaVuota();
}


template<class T>
void Lista<T>::inserireLista(const tipo &elemento, posizione p){

	ListNode<T>* n = new ListNode<T>;
	n->valore = elemento;
	n->succ = testa;
	n->prec = testa->prec;
	testa->prec->succ = n;
	testa->prec = n;
	lunghezza++;
}


template<class T>
void Lista<T>::cancellaLista(posizione p){

	if (!listaVuota())
	{
		if(p != testa)
		{
			p->prec->succ = p->succ;
			p->succ->prec = p->prec;
			delete p;
		}
	}
}



/****
Inverte la lista utilizzando solo i puntatori.
Tramita l'utilizzo di variabili temporanee inverte le posizioni Prec e Succ di ogni nodo
L'aggiornamento della Testa viene fatto alla fine

template<class T>
void Lista<T>::inverti(){

	posizione nodoCorrente, nodoSuccessivo, nodoTemp;

	nodoTemp = primoLista();
	nodoCorrente = primoLista();
	while(nodoCorrente != ultimoLista()){
		nodoSuccessivo = nodoCorrente->succ;
		nodoCorrente->succ = nodoCorrente->prec;
		nodoCorrente->prec = nodoSuccessivo;
		nodoCorrente = nodoSuccessivo;
	}

	nodoCorrente->succ = nodoCorrente->prec;
	nodoCorrente->prec = testa;
	testa->succ = nodoCorrente;
	testa->prec = nodoTemp;

}

*/

			/********** Overloading operatori **********/
template<class T>
Lista<T>& Lista<T>::operator=(const Lista<T>& L){

	if (this != &L)
	{
		~Lista();
		creaLista();
		if (!L.listaVuota())
		{
			for(posizione p = L.primoLista(); !L.fineLista(p); p = L.successivo(p)){
				inserireLista(L.leggiLista(p), ultimoLista());
			}
		}
	}
	return *this;
}


#endif /* LISTA_H_ */
