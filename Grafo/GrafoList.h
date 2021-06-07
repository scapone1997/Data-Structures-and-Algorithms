/*
 * GrafoList.h
 *
 *  Created on: 18 dic 2020
 *      Author: vcapo
 */

#ifndef GRAFOLIST_H_
#define GRAFOLIST_H_

#include "Grafo_astratto.h"
#include <vector>

class NodoG{
	public:
		NodoG(int i){nodo_id = i;}
		NodoG(){nodo_id = -1;}
		NodoG(const NodoG& n){nodo_id = n.nodo_id;}
		NodoG(const NodoG* n){nodo_id = n->nodo_id;}
		int get_id(){ return nodo_id; }
		void set_id(int id){ nodo_id = id; }

		friend ostream& operator<<(ostream& os, const NodoG* n){
			os << n->nodo_id;
			return os;
		}

		friend ostream& operator<<(ostream& os, const NodoG n){
			os << n.nodo_id;
			return os;
		}

		bool operator==(const NodoG& n){return (nodo_id == n.nodo_id);}
		bool operator==(const NodoG* n){return (nodo_id == n->nodo_id);}

	private:
		int nodo_id;
};


template<class P>
class InfoArco{
	public:
		P peso;
		NodoG _to;

		friend ostream& operator<<(ostream& os, const InfoArco<P>& a){
			os << "[Peso :" << a.peso << ",";
			os << "verso->" << a._to << "]";
			return os;
		}
};


template<class E, class P>
class InfoNodo{
	public:
		E etichetta;
		bool vuoto;
		int info;
		Lista<InfoArco<P>> archi;

		InfoNodo(){
			info = 0;
			vuoto = true;
		}
};



template<class E, class P>
class GrafoList : public Grafo<E, P, NodoG>{

	public:
    	typedef E Etichetta;
    	typedef P Peso;
    	typedef NodoG Nodo;
    	typedef Arco_<Peso, Nodo> Arco;
    	typedef Grafo<Etichetta, Peso, Nodo> Grafo_;
    	typedef typename Grafo_::ListaNodi ListaNodi;
    	typedef typename Grafo_::ListaNodiPos ListaNodiPos;

    	GrafoList();
    	GrafoList(int);
    	~GrafoList();

    	bool vuoto() const;
    	void ins_nodo(NodoG&);
    	void ins_arco(Nodo, Nodo, Peso);
    	void canc_nodo(Nodo);
    	void canc_arco(Nodo, Nodo);
    	bool esiste_nodo(Nodo);
    	bool esiste_arco(Nodo, Nodo);
    	ListaNodi adiacenti(Nodo) const;
    	ListaNodi lista_nodi() const;
    	Etichetta leggi_etichetta(Nodo) const;
    	void scrivi_etichetta(Nodo, Etichetta);
    	Peso leggi_peso(Nodo, Nodo) const;
    	void scrivi_peso(Nodo, Nodo, Peso);
    	int num_nodi(){return nodi;};
    	int num_archi(){return archi;};
    	int num_archi_entranti(Nodo); //Lab
    	int num_archi_uscenti(Nodo); //Lab
    	double mean_out_degree(); //Lab: media del numero di archi uscenti per ogni nodo del grafo
    	void find_path(Nodo, Nodo); //Lab
    	void trasposto(); //Lab
    	//bool esiste(Etichetta) const;
    	void BFS(Nodo);
    	void DFS(Nodo);
    	void DFS(Nodo, DCoda<Nodo>& L);

    	//Overloading <<
    	friend ostream& operator<<(ostream& os, const GrafoList<E, P>& G){
    		Lista<NodoG*> LN = G.lista_nodi();
    		cout << "Lista nodi: [";
    		if(!LN.listaVuota())
    		{
    			Lista<NodoG*>::posizione ln = LN.primoLista();
    			while(!LN.fineLista(ln))
    			{
    				cout << G.leggi_etichetta(*(LN.leggiLista(ln)));
    				cout << ",";
    				ln = LN.successivo(ln);
    			}
    		}
    		cout << "]" << endl;

    		for(int i = 0; i < G.dimensione; i++)
    		{
    			if(G.matrice[i].vuoto == false)
    			{
    				Lista<InfoArco<P>> A = G.matrice[i].archi;
    				cout << "[" << A.dimensione() << "]:";
    				cout << " Adiacenti di " << G.matrice[i].etichetta << "--> ";
    				if(!A.listaVuota())
    				{
    					typename Lista<InfoArco<P>>::posizione a = A.primoLista();
            			while(!A.fineLista(a))
            			{
            				cout << G.leggi_etichetta(A.leggiLista(a)._to);
            				cout << " ";
            				a = A.successivo(a);
            			}
    				}
    			}
    			cout << endl;
    		}
    		os << "Nodi: " << G.nodi << endl;
    		os << "Archi: " << G.archi << endl;
    		return os;
    	}

	private:
    	void find_path(Nodo, Nodo, DCoda<Nodo>&, DCoda<Nodo>&);
    	InfoNodo<E,P>* matrice;
    	int dimensione;
    	int nodi;
    	int archi;
};

//OK

template<class E, class P>
GrafoList<E, P>::GrafoList(){

	dimensione = 10;
	nodi = 0;
	archi = 0;
	matrice = new InfoNodo<E,P>[dimensione];
	for(int i=0; i<dimensione; i++)
		matrice[i].archi.creaLista();
}


template<class E, class P>
GrafoList<E, P>::GrafoList(int d){

	dimensione = d;
	nodi = 0;
	archi = 0;
	matrice = new InfoNodo<E,P>[dimensione];
	for(int i=0; i<dimensione; i++)
		matrice[i].archi.creaLista();
}

//Ok
template<class E, class P>
GrafoList<E, P>::~GrafoList(){

	delete[] matrice;
}

//Ok
template<class E, class P>
bool GrafoList<E, P>::vuoto() const{

	return(nodi == 0);
}

//Ok
template<class E, class P>
void GrafoList<E, P>::ins_nodo(Nodo& N){

	int n = 0;
	if(nodi < dimensione)
	{
		while(matrice[n].vuoto == false)
			n++;
		nodi++;
		matrice[n].vuoto = false;
	}
	N.set_id(n);
}

//Ok
template<class E, class P>
void GrafoList<E, P>::ins_arco(Nodo n1, Nodo n2, P peso){

	InfoArco<P> I;
	I.peso = peso;
	I._to = n2;
	matrice[n1.get_id()].archi.inserireLista(I, matrice[n1.get_id()].archi.primoLista());
	archi++;
}

//Sembra andare bene
template<class E, class P>
void GrafoList<E, P>::canc_nodo(Nodo n){

	bool canc = true;
	if(matrice[n.get_id()].archi.listaVuota())
	{
		ListaNodi L = lista_nodi();
		while(!L.listaVuota() && canc == true)
		{
			ListaNodi A = adiacenti(*(L.leggiLista(L.primoLista())));
			while(!A.listaVuota())
			{
				if(A.leggiLista(A.primoLista())->get_id() == n.get_id())
					canc = false;
				A.cancellaLista(A.primoLista());
			}
			L.cancellaLista(L.primoLista());
		}

		if(canc == true)
		{
			matrice[n.get_id()].vuoto = true;
			nodi--;
		}
		else
			cout << "Esistono archi entranti da questo nodo!" << endl;
	}
	else
		cout << "Esisono archi uscenti da questo nodo!" << endl;
}


template<class E, class P>
void GrafoList<E, P>::canc_arco(Nodo n1, Nodo n2){

	typename Lista<InfoArco<P> >::posizione p;
	p = matrice[n1.get_id()].archi.primoLista();
	bool trovato = false;
	while (!matrice[n1.get_id()].archi.fineLista(p) && !trovato){
		if (matrice[n1.get_id()].archi.leggiLista(p)._to.get_id() == n2.get_id())
			trovato = true;
		else
			p = matrice[n1.get_id()].archi.successivo(p);
	}

	if (trovato)
	{
		matrice[n1.get_id()].archi.cancellaLista(p);
		archi--;
	}

}

//Ok
template<class E, class P>
bool GrafoList<E, P>::esiste_nodo(Nodo n1){

	bool esiste = false;
	ListaNodi L = lista_nodi();
	for(typename ListaNodi::posizione l = L.primoLista();
			!L.fineLista(l) && esiste == false; l = L.successivo(l))
	{
		if(L.leggiLista(l)->get_id() == n1.get_id())
			esiste = true;
	}
	return esiste;
}

//Ok
template<class E, class P>
bool GrafoList<E, P>::esiste_arco(Nodo n1, Nodo n2){

	bool esiste = false;
	ListaNodi A = adiacenti(n1);
	for(typename ListaNodi::posizione a = A.primoLista();
				!A.fineLista(a) && esiste == false; a = A.successivo(a))
	{
		if(A.leggiLista(a)->get_id() == n2.get_id())
			esiste = true;
	}
	return esiste;
}


//Ok
template<class E, class P>
typename GrafoList<E, P>::ListaNodi GrafoList<E, P>::adiacenti(Nodo n) const{

	Lista<InfoArco<P>> A(matrice[n.get_id()].archi);
	Lista<Nodo*> LN;

	if(!A.listaVuota())
	{
		typename Lista<InfoArco<P>>::posizione a = A.primoLista();
		while(!A.fineLista(a))
		{
			LN.inserireLista(new NodoG(A.leggiLista(a)._to), LN.primoLista());
			a = A.successivo(a);
		}
	}
	return LN;
}

//Ok
template<class E, class P>
typename GrafoList<E, P>::ListaNodi GrafoList<E, P>::lista_nodi() const{

	Lista<Nodo*> L;
	for(int i = 0; i < dimensione; i++)
		if(!matrice[i].vuoto)
			L.inserireLista(new NodoG(i), L.primoLista());
	return L;
}

//Ok
template<class E, class P>
E GrafoList<E, P>::leggi_etichetta(Nodo n) const{

	return matrice[n.get_id()].etichetta;
}

//Ok
template<class E, class P>
void GrafoList<E, P>::scrivi_etichetta(Nodo n, E etichetta){

	matrice[n.get_id()].etichetta = etichetta;
}


//Ok
template<class E, class P>
P GrafoList<E, P>::leggi_peso(Nodo n1, Nodo n2) const{

	typename Lista<InfoArco<P> >::posizione p;
	p = matrice[n1.get_id()].archi.primoLista();
	bool trovato = false;
	while(!matrice[n1.get_id()].archi.fineLista(p) && !trovato)
	{
		if(matrice[n1.get_id()].archi.leggiLista(p)._to.get_id() == n2.get_id())
			trovato = true;
		else
			p = matrice[n1.get_id()].archi.successivo(p);
	}

	if(trovato)
		return matrice[n1.get_id()].archi.leggiLista(p).peso;
}


//Ok
template<class E, class P>
void GrafoList<E, P>::scrivi_peso(Nodo n1, Nodo n2, P peso){

	typename Lista<InfoArco<P>>::posizione p;
	p = matrice[n1.get_id()].archi.primoLista();
	bool trovato = false;
	while(!matrice[n1.get_id()].archi.fineLista(p) && !trovato)
	{
		if(matrice[n1.get_id()].archi.leggiLista(p)._to.get_id() == n2.get_id())
			trovato = true;
		else
			p = matrice[n1.get_id()].archi.successivo(p);
	}

	if(trovato)
	{
		InfoArco<P> I;
		I.peso = peso;
		I._to = n2;
		matrice[n1.get_id()].archi.scriviLista(I,p);
	}
}


template<class E, class P>
int GrafoList<E, P>::num_archi_entranti(Nodo n){

	int archi_entranti = 0;
	for(int i = 0; i< dimensione; i++)
	{
		if(!matrice[i].archi.listaVuota())
		{
			if(matrice[i].vuoto == false)
			{
				typename Lista<InfoArco<P>>::posizione p;
				p = matrice[i].archi.primoLista();
				while(!matrice[i].archi.fineLista(p))
				{
					if(matrice[i].archi.leggiLista(p)._to.get_id() == n.get_id())
						archi_entranti++;
					p = matrice[i].archi.successivo(p);
				}
			}
		}
	}
	return archi_entranti;
}


template<class E, class P>
int GrafoList<E, P>::num_archi_uscenti(Nodo n){

	return (matrice[n.get_id()].archi.dimensione());
}


template<class E, class P>
double GrafoList<E, P>::mean_out_degree(){

	double somma_uscenti = 0;
	for(int i = 0; i< dimensione; i++)
		somma_uscenti += matrice[i].archi.dimensione();
	double media = somma_uscenti/num_nodi();
	return media;
}


template<class E, class P>
void GrafoList<E, P>::find_path(Nodo a, Nodo b){

	DCoda<Nodo> path;
	DCoda<Nodo> visitati;
	find_path(a, b, path, visitati);
}

template<class E, class P>
void GrafoList<E, P>::find_path(Nodo a, Nodo b, DCoda<Nodo>& path, DCoda<Nodo>& visitati){

	visitati.inserireRetro(a);
	path.inserireRetro(a);
	if(a.get_id() == b.get_id())
	{
		string color = leggi_etichetta(path.leggiFronte());
		while(!path.codaVuota())
		{
			if(path.dimensione()>1)
				cout << matrice[path.leggiFronte().get_id()].etichetta + "->";
			else
				cout << matrice[path.leggiFronte().get_id()].etichetta << endl;
			path.cancellaFronte();
		}
	}
	else
	{
		Lista<Nodo*> A = adiacenti(a);
		typename Lista<Nodo*>::posizione ap = A.primoLista();
		while(!A.fineLista(ap))
		{
			if(!visitati.esiste(A.leggiLista(ap)))
				find_path(A.leggiLista(ap), b, path, visitati);
			ap = A.successivo(ap);
		}
		path.cancellaRetro();
	}
}


//Funziona ma si può ottimizzare meglio!!
template<class E, class P>
void GrafoList<E, P>::trasposto(){

	vector<Lista<Nodo*>> v;
	vector<int> v_id;
	vector<Lista<int>> v_pesi;
	Lista<Nodo*> nodi = lista_nodi();

	for(typename Lista<Nodo*>::posizione n = nodi.primoLista();
			        !nodi.fineLista(n); n = nodi.successivo(n))
	{
		Lista<Nodo*> A = adiacenti(nodi.leggiLista(n));
		v.push_back(A);
		v_id.push_back(nodi.leggiLista(n)->get_id());

		Lista<int> pesi;
		for(typename Lista<Nodo*>::posizione a = A.primoLista();
			               !A.fineLista(a); a = A.successivo(a))
		{
			pesi.inserireLista(leggi_peso(nodi.leggiLista(n),
					    A.leggiLista(a)), pesi.primoLista());
			canc_arco(nodi.leggiLista(n), A.leggiLista(a));
		}
		v_pesi.push_back(pesi);
	}

	unsigned int i = 0;
	while(i<v.size())
	{
		typename Lista<int>::posizione t = v_pesi[i].primoLista();
		for(typename Lista<Nodo*>::posizione p = v[i].primoLista();
				!v[i].fineLista(p); p = v[i].successivo(p)){
			ins_arco(new NodoG(v[i].leggiLista(p)->get_id()), new NodoG(v_id[i]),
					v_pesi[i].leggiLista(t));
			t = v_pesi[i].successivo(t);
		}
		i++;
	}
}



////Ok, Testato con AB: Ricerca livello per livello (livello 0, 1, 2)
template<class E, class P>
void GrafoList<E, P>::BFS(Nodo n){

	DCoda<Nodo> Q; //Coda dei nodi da visitare
	DCoda<Nodo> V; //Coda dei nodi visitati
	Q.inserireRetro(n);
	while(!Q.codaVuota())
	{
		Nodo k = Q.leggiRetro();
		Q.cancellaRetro();
		cout << "visita:" << leggi_etichetta(k) << endl;
		V.inserireRetro(k);
		Lista<Nodo*> A = adiacenti(k);
		typename Lista<Nodo*>::posizione a = A.primoLista();
		while(!A.fineLista(a))
		{
			if(!V.esiste(A.leggiLista(a)) && !(Q.esiste(A.leggiLista(a))))
			{
				Q.inserireFronte(A.leggiLista(a));
			}
			a = A.successivo(a);
		}
	}
}


//OK, Testato con AB: Ricerca in profondita..scende fino alla foglia e risale
template<class E, class P>
void GrafoList<E, P>::DFS(Nodo n){

	DCoda<Nodo> C;
	DFS(n, C);
}


template<class E, class P>
void GrafoList<E, P>::DFS(Nodo n, DCoda<Nodo>& C){

	if(!C.esiste(n))
	{
		cout << "visita:" << matrice[n.get_id()].etichetta << endl; //visita
		C.inserireRetro(n);
		Lista<Nodo*> A = adiacenti(n);
		typename Lista<Nodo*>::posizione a = A.primoLista();
		while(!A.fineLista(a))
		{
			DFS(A.leggiLista(a), C);
			a = A.successivo(a);
		}
	}
}



#endif /* GRAFOLIST_H_ */
