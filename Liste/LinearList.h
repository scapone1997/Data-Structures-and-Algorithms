/*
 * LinearList.h
 *
 *  Created on: 31 ott 2020
 *      Author: vcapo
 */

#ifndef LINEARLIST_H_
#define LINEARLIST_H_

#include <iostream>
using namespace std;

template<class T, class P>
class LinearList{

	public:
		typedef T tipo;
		typedef P posizione;

		virtual void creaLista() = 0;
		virtual bool listaVuota() const = 0;
		virtual tipo leggiLista(posizione) const = 0;
		virtual void scriviLista(const tipo&, posizione) = 0;
		virtual posizione primoLista() const = 0;
		virtual bool fineLista(posizione) const = 0;
		virtual posizione precedente(posizione) const = 0;
		virtual posizione successivo(posizione) const = 0;
		virtual void inserireLista(const tipo&, posizione) = 0;
		virtual void cancellaLista(posizione) = 0;
		virtual posizione ultimoLista() const = 0;

		//Metodi generici
		bool esiste(const tipo& e) const;
		int dimensione() const; //Ok
		void inverti(); //Ok
		void clear();
		int num_elementi(posizione, posizione); //Ok
		void exchange(posizione, posizione); //Ok
		void move_min_max(); //???
		bool palindroma() const; //Ok
		bool operator==(const LinearList<T,P>&) const; //Ok
		bool operator!=(const LinearList<T,P>&) const; //Ok


};

//Overloading <<
template<class T, class P>
ostream& operator<<(ostream& os, const LinearList<T, P>& lista){

	typename LinearList<T,P>::posizione p;
	p = lista.primoLista();
	cout << "[";
	while (!lista.fineLista(p)){
		if (p != lista.primoLista())
			cout << ", " << lista.leggiLista(p);
		else
			cout << lista.leggiLista(p);
		p = lista.successivo(p);
	}
	cout << "]" << endl;
	return os;
}

template<class T, class P>
bool LinearList<T, P>::esiste(const tipo& e) const{

	bool esito = false;
	if (!listaVuota())
	{
		posizione p = primoLista();
		while(!fineLista(p) && esito == false)
		{
			if(leggiLista(p) == e)
				esito = true;
			p = successivo(p);
		}
	}
	return esito;
}

template<class T, class P>
int LinearList<T, P>::dimensione() const{

	LinearList<T, P>::posizione p;
	int dimensione = 0;
	for (p = primoLista(); !fineLista(p); p = successivo(p))
		dimensione++;

	return dimensione;
}

template<class T, class P>
void LinearList<T, P>::inverti() {

	LinearList<T, P>::posizione sinistra;
	LinearList<T, P>::posizione destra;

	sinistra = primoLista();
	destra = primoLista();
	//trovo l'ultima posizione
	while(!fineLista(successivo(destra)))
		destra = successivo(destra);

	LinearList<T, P>::tipo v;
	while(sinistra != destra && destra != precedente(sinistra)){
		v = leggiLista(sinistra);
		scriviLista(leggiLista(destra), sinistra);
		scriviLista(v, destra);
		sinistra = successivo(sinistra);
		destra = precedente(destra);
	}
}

template<class T, class P>
void LinearList<T, P>::clear(){

	while(!listaVuota())
		cancellaLista(primoLista());
}

template<class T, class P>
int LinearList<T, P>::num_elementi(posizione p1, posizione p2){

	if(!listaVuota())
	{
		LinearList<T, P>::posizione p = p1;
		int c = 1;
		while(p != p2){
			p = successivo(p);
			c++;
		}
		return c;
	}
	else
		return 0;
}

template<class T, class P>
void LinearList<T, P>::exchange(LinearList<T, P>::posizione p1, LinearList<T, P>::posizione p2){

	T temp = leggiLista(p1);
	scriviLista(leggiLista(p2), p1);
	scriviLista(temp, p2);
}

template<class T, class P>
void LinearList<T, P>::move_min_max(){

	if(!listaVuota())
	{
		T min, max;
		LinearList<T, P>::posizione p = primoLista();
		LinearList<T, P>::posizione pos_min = primoLista();
		LinearList<T, P>::posizione pos_max = primoLista();
		min = leggiLista(pos_min);
		max = leggiLista(pos_max);
		while(!fineLista(p))
		{
			if(leggiLista(p) < min)
			{
				min = leggiLista(p);
				pos_min = p;
			}
			if(leggiLista(p) > max)
			{
				max = leggiLista(p);
				pos_max = p;
			}
			p = successivo(p);
		}
		//min e max sono i valori massimi
		//pos_min e pos_max le relative posizioni!!!
	}
}

template<class T, class P>
bool LinearList<T, P>::palindroma() const{

	LinearList<T, P>::posizione sinistra;
	LinearList<T, P>::posizione destra;

	sinistra = primoLista();
	destra = primoLista();
	while(!fineLista(successivo(destra)))
		destra = successivo(destra);

	bool esito = true;
	LinearList<T, P>::tipo v;
	while(sinistra != destra && destra != precedente(sinistra) && esito == true){
		if(leggiLista(sinistra) != leggiLista(destra))
			esito = false;
		sinistra = successivo(sinistra);
		destra = precedente(destra);
	}

	return esito;
}

template<class T, class P>
bool LinearList<T, P>::operator==(const LinearList<T, P>& altra) const{

	bool esito = true;
	if (altra.dimensione() != this->dimensione())
		esito = false;
	else
	{
		typename LinearList<T, P>::posizione p, pL;
		p = primoLista();
		pL = altra.primoLista();
		while (!fineLista(p) && esito == true)
		{
			if (leggiLista(p) != altra.leggiLista(pL))
				esito = false;
			p = successivo(p);
			pL = successivo(pL);
		}
	}
	return esito;
}

template<class T, class P>
bool LinearList<T, P>::operator!=(const LinearList<T, P>& altra) const{

	bool esito = false;
	if (altra.dimensione() != this->dimensione())
		esito = true;
	else
	{
		typename LinearList<T, P>::posizione p, pL;
		p = primoLista();
		pL = altra.primoLista();
		while (!fineLista(p) && esito == false)
		{
			if (leggiLista(p) != altra.leggiLista(pL))
				esito = true;
			p = successivo(p);
			pL = successivo(pL);
		}
	}
	return esito;
}

#endif /* LINEARLIST_H_ */
