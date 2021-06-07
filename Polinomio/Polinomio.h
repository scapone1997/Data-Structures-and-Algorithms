/*
 * Polinomio.h
 *
 *  Created on: 25 dic 2020
 *      Author: vcapo
 */

#ifndef POLINOMIO_H_
#define POLINOMIO_H_

#include <iostream>
#include <cmath>
#include <vector>
#include "Lista\Lista.h"
using namespace std;

class Polinomio{

	public:
		Polinomio(){
			C.inserireLista(0.0, C.primoLista());
		}

		Polinomio(vector<double>& s){
			for(unsigned int i = 0; i < s.size(); i++)
				C.inserireLista(s[i], C.primoLista());
		}

		int grado(){
			return (C.dimensione()-1);
		}

		void somma(Polinomio& P){
			Lista<double>::posizione p1, p2;
			p1 = C.primoLista();
			p2 = P.C.primoLista();
			while(!C.fineLista(p1) && !P.C.fineLista(p2))
			{
				C.scriviLista(C.leggiLista(p1) + P.C.leggiLista(p2), p1);
				p1 = C.successivo(p1);
				p2 = P.C.successivo(p2);
			}
			if(C.fineLista(p1))
			{
				while(!P.C.fineLista(p2))
				{
					C.inserireLista(P.C.leggiLista(p2), C.ultimoLista());
					p2 = P.C.successivo(p2);
				}
			}
		}

		double valore(double x){
			double c = 0;
			int g = 0;
			Lista<double>::posizione p = C.primoLista();
			while(!C.fineLista(p))
			{
				c = c + (pow(x, g) * C.leggiLista(p));
				g++;
				p = C.successivo(p);
			}
			return c;
		}

		friend ostream& operator<<(ostream& os, const Polinomio& P){
			Lista<double>::posizione p = P.C.ultimoLista();
			int i = P.C.dimensione()-1;
			while(!P.C.fineLista(p))
			{
				if(i == 0)
					os << P.C.leggiLista(p);
				else
					os << P.C.leggiLista(p) << "x^" << i << " + ";
				p = P.C.precedente(p);
				i--;
			}
			os << endl;
			return os;
		}

	private:
		Lista<double> C;
};

#endif /* POLINOMIO_H_ */
