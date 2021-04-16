/*
 * LAB 9: Realizzare la ADT Alberi Binari mediante vettore sequenziale.
 *
 *
 */

#ifndef ALBERO_BINARIO_V_H_
#define ALBERO_BINARIO_V_H_

#include <iostream>
#include "Albero_binario_astratto.h"

template <class T>
class Albero_binario_v : public Albero_binario_astratto<T, int>{

	public:
		typedef typename Albero_binario_astratto<T, int>::tipo tipo;
		typedef typename Albero_binario_astratto<T, int>::Nodo Nodo;

		struct cella {
			Nodo genitore;
			Nodo sinistro;
			Nodo destro;
			tipo valore;
		};

		typedef struct cella Cella;

		//Costruttori e distruttore
		Albero_binario_v();
		Albero_binario_v(int n_nodi);
		~Albero_binario_v();

		//Operatori
		void crea();
		bool vuoto() const;
		Nodo radice() const;
		Nodo genitore(Nodo) const;
		Nodo sinistro(Nodo) const;
		Nodo destro(Nodo) const;
		bool sinistro_vuoto(Nodo) const;
		bool destro_vuoto(Nodo) const;
		void cancella(Nodo);
		T leggi(Nodo) const;
		void scrivi(Nodo, tipo);
		void inserire_radice(Nodo);
		void inserire_sinistro(Nodo);
		void inserire_destro(Nodo);

	private:
		static const int NIL = -1;
	    int lunghezza_max;
	    Cella *spazio;
	    int n_nodi;
	    Nodo inizio;
	    Nodo libero;

};

template <class T>
Albero_binario_v<T>::Albero_binario_v(){

	lunghezza_max = 100;
	spazio = new Cella[lunghezza_max];
	crea();
}

template <class T>
Albero_binario_v<T>::Albero_binario_v(int n_nodi){

	lunghezza_max = n_nodi;
	spazio = new Cella[lunghezza_max];
	crea();
}

template <class T>
Albero_binario_v<T>::~Albero_binario_v(){

	cancella(inizio);
	delete[] spazio;
}

template <class T>
void Albero_binario_v<T>::crea(){

	inizio = NIL;
	libero = 0;
	n_nodi = 0;

	for (int i = 0; i < lunghezza_max; i++)
		spazio[i].sinistro = (i+1) % lunghezza_max;

}

template <class T>
bool Albero_binario_v<T>::vuoto() const{

	return(n_nodi == 0);
}

template <class T>
typename Albero_binario_v<T>::Nodo Albero_binario_v<T>::radice() const{

	return inizio;
}

template <class T>
typename Albero_binario_v<T>::Nodo Albero_binario_v<T>::genitore(Nodo n) const{

	return spazio[n].genitore;
}

template <class T>
typename Albero_binario_v<T>::Nodo Albero_binario_v<T>::sinistro(Nodo n) const{

	if (!sinistro_vuoto(n))
		return (spazio[n].sinistro);
	else
		return NIL;
};

template <class T>
typename Albero_binario_v<T>::Nodo Albero_binario_v<T>::destro(Nodo n) const {

	if (!destro_vuoto(n))
		return (spazio[n].destro);
	else
		return NIL;
}

template <class T>
bool Albero_binario_v<T>::sinistro_vuoto(Nodo n) const{

	return (spazio[n].sinistro == NIL);
}

template <class T>
bool Albero_binario_v<T>::destro_vuoto(Nodo n) const{

	return (spazio[n].destro == NIL);
}

template <class T>
void Albero_binario_v<T>::inserire_radice(Nodo n){

	if (inizio == NIL)
    {
		inizio = libero;
		libero = spazio[libero].sinistro;
		spazio[inizio].sinistro = NIL;
		spazio[inizio].destro = NIL;
		n_nodi++;
    }
	else
		throw RadiceEsiste();
}

template <class T>
void Albero_binario_v<T>::inserire_sinistro(Nodo n){

	if (inizio == NIL)
		throw AlberoVuoto();
	if (n == NIL)
		throw NodoNullo();
	if (spazio[n].sinistro != NIL)
		throw NodoEsiste();
	if (n_nodi >= lunghezza_max)
		throw AlberoPieno();
	else
    {
		Nodo q = libero;
		libero = spazio[libero].sinistro;
		spazio[n].sinistro = q;
		spazio[q].genitore = n;
		spazio[q].sinistro = NIL;
		spazio[q].destro = NIL;
		n_nodi++;
    }
}

template <class T>
void Albero_binario_v<T>::inserire_destro(Nodo n){

	if (inizio == NIL)
		throw AlberoVuoto();
	if (n == NIL)
		throw NodoNullo();
	if (spazio[n].destro != NIL)
		throw NodoEsiste();
	if (n_nodi >= lunghezza_max)
		throw AlberoPieno();
	else
    {
		Nodo q = libero;
		libero = spazio[libero].sinistro;
		spazio[n].destro = q;
		spazio[q].genitore = n;
		spazio[q].sinistro = NIL;
		spazio[q].destro = NIL;
		n_nodi++;
    }
}

template <class T>
void Albero_binario_v<T>::cancella(Nodo n){

	if (n != NIL)
	{
			if (!sinistro_vuoto(n))
				cancella(spazio[n].sinistro);
			if (!destro_vuoto(n))
				cancella(spazio[n].destro);
			if (n != inizio)
			{
				Nodo p = genitore(n);
				if (spazio[p].sinistro == n)
					spazio[p].sinistro = NIL;
				else
					spazio[p].destro = NIL;
			}
			else
				inizio = NIL;

      n_nodi--;
      spazio[n].sinistro = libero;
      libero = n;
    }
}

template <class T>
T Albero_binario_v<T>::leggi(Nodo n) const{

	if (n != NIL)
		return (spazio[n].valore);
	else
		throw NodoNullo();
}

template <class T>
void Albero_binario_v<T>::scrivi(Nodo n, tipo elemento){

	if (n != NIL)
		spazio[n].valore = elemento;
	else
		throw NodoNullo();
}


#endif /* ALBERO_BINARIO_V_H_ */
