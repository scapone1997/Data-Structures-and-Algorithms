/*
 * Grafo_astratto.h
 *
 *  Created on: 16 dic 2020
 *      Author: vcapo
 */

#ifndef GRAFO_ASTRATTO_H_
#define GRAFO_ASTRATTO_H_

#include "C:\Users\vcapo\Desktop\Progetti\Coda\DCoda.h"
#include "Lista\Lista.h"

template<class P, class N>
class Arco_{
	public:
		N nodo1;
		N nodo2;
		P peso;
};


template<class E, class P, class N>
class Grafo{
	public:
		typedef E Etichetta;
		typedef P Peso;
		typedef N Nodo;
		typedef Arco_<Peso, Nodo> Arco;
		typedef Lista<Nodo*> ListaNodi;
		typedef typename Lista<Nodo*>::posizione ListaNodiPos;
		typedef Lista<Arco> ListaArchi;

		virtual bool vuoto() const = 0;
		virtual void ins_nodo(Nodo&) = 0;
		virtual void ins_arco(Nodo, Nodo, Peso) = 0;
		virtual void canc_nodo(Nodo) = 0;
		virtual void canc_arco(Nodo, Nodo) = 0;
		virtual bool esiste_nodo(Nodo) = 0;
		virtual bool esiste_arco(Nodo, Nodo) = 0;
		virtual ListaNodi adiacenti(Nodo) const = 0;
		virtual ListaNodi lista_nodi() const = 0;
		virtual Etichetta leggi_etichetta(Nodo) const = 0;
		virtual void scrivi_etichetta(Nodo, Etichetta) = 0;
		virtual Peso leggi_peso(Nodo, Nodo) const = 0;
		virtual void scrivi_peso(Nodo, Nodo, Peso) = 0;
		virtual int num_nodi() = 0;
		virtual int num_archi() = 0;
		virtual int num_archi_entranti(Nodo) = 0;
		virtual int num_archi_uscenti(Nodo) = 0;
		virtual ~Grafo(){};

};


#endif /* GRAFO_ASTRATTO_H_ */
