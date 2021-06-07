/*
 * tester.cpp
 *
 *  Created on: 17 dic 2020
 *      Author: vcapo
 */

#include "GrafoList.h"
#include <string>
#include <list>
using namespace std;

void BFS(GrafoList<string, double>& G, NodoG n);
void DFS(GrafoList<string, double>& G, NodoG n, DCoda<NodoG>& C);
void DFS(GrafoList<string, double>& G, NodoG n);

void stampa_tutti_path(GrafoList<int, int>& G, NodoG a, NodoG b);
void stampa_tutti_path(GrafoList<int, int>& G, NodoG a, NodoG b,
		bool visited[], NodoG path[], int& path_index);

int main(){

	//Creo un nuovo Grafo G
	GrafoList<int, int> G(5);
	NodoG a, b, c, d, e;

	//Inserisco i nodi e i vari collegamenti
	G.ins_nodo(a);
	G.scrivi_etichetta(a, 0);
	G.ins_nodo(b);
	G.scrivi_etichetta(b, 1);
	G.ins_nodo(c);
	G.scrivi_etichetta(c, 2);
	G.ins_nodo(d);
	G.scrivi_etichetta(d, 3);
	G.ins_nodo(e);
	G.scrivi_etichetta(e, 4);

	//Inserisco gli archi
	G.ins_arco(a, b, 4);
	G.ins_arco(a, c, 8);
	G.ins_arco(b, c, 17);
	G.ins_arco(a, e, 11);
	G.ins_arco(b, a, 13);
	G.ins_arco(d, a, 15);
	G.ins_arco(d, b, 19);
	cout << G;

	stampa_tutti_path(G, a, c);



	system("PAUSE");
	return 0;

}

void BFS(GrafoList<string, double>& G, NodoG n){
	DCoda<NodoG> Q; //Coda dei nodi da visitare
	DCoda<NodoG> V; //Coda dei nodi visitati
	Q.inserireRetro(n);
	while(!Q.codaVuota())
	{
		cout << "Q:" << Q;
		cout << "V:" << V;
		NodoG k = Q.leggiRetro();
		Q.cancellaRetro();
		cout << "visita:" << G.leggi_etichetta(k) << endl;
		V.inserireRetro(k);
		Lista<NodoG*> A = G.adiacenti(k);
		typename Lista<NodoG*>::posizione a = A.primoLista();
		while(!A.fineLista(a))
		{
			if(!V.esiste(A.leggiLista(a)) && !(Q.esiste(A.leggiLista(a))))
			{
				Q.inserireFronte(A.leggiLista(a));
			}
			a = A.successivo(a);
		}
	}
	cout << "C conclusiva:" << Q;
	cout << "V conclusiva:" << V;
}


void DFS(GrafoList<string, double>& G, NodoG n){

	DCoda<NodoG> C;
	DFS(G, n, C);
	cout << C << endl;
}


void DFS(GrafoList<string, double>& G, NodoG n, DCoda<NodoG>& C){

	if(!C.esiste(n))
	{
		cout << "visita:" << G.leggi_etichetta(n) << endl; //visita
		C.inserireRetro(n);
		cout << "C: " << C;
		Lista<NodoG*> A = G.adiacenti(n);
		typename Lista<NodoG*>::posizione a = A.primoLista();
		while(!A.fineLista(a))
		{
			DFS(G, A.leggiLista(a), C);
			a = A.successivo(a);
		}
	}
}


void stampa_tutti_path(GrafoList<int, int>& G, NodoG a, NodoG b){

	//Marco tutti i vertici come non visitati
	int V = G.lista_nodi().dimensione();
    bool* visited = new bool[V];

    //Creo un array per memorizzare i path
    NodoG* path = new NodoG[V];
    int path_index = 0; // Initialize path[] as empty

    //Inizializzo tutti i vertici come non visitati
    for (int i = 0; i < V; i++)
        visited[i] = false;

    //Chiamo la funzione ricorsiva per stampare tutti i possibili path
    stampa_tutti_path(G, a, b, visited, path, path_index);

}


void stampa_tutti_path(GrafoList<int, int>& G, NodoG a, NodoG b,
		bool visited[], NodoG path[], int& path_index){

	//Marco il nodo corrente come visitato e lo metto nel path
    visited[a.get_id()] = true;
    path[path_index] = a;
    path_index++;

    //Se il vertice corrente è uguale alla destinazione, allora
    //stampo il path
    if (a == b)
    {
        for (int i = 0; i < path_index; i++)
            cout << path[i] << " ";
        cout << endl;
    }
    else //Se il vertice corrente non è la destinazione
    {
    	//Itero il procedimento per tutti i nodi adiacenti di a
        Lista<NodoG*> A = G.adiacenti(a);
        typename Lista<NodoG*>::posizione a;
        for (a = A.primoLista(); !A.fineLista(a); a = A.successivo(a))
            if (!visited[A.leggiLista(a)->get_id()])
            	stampa_tutti_path(G, A.leggiLista(a), b, visited, path, path_index);
    }

    //Rimuovo il vertice corrente dal path[] e lo marco come non visitato
    path_index--;
    visited[a.get_id()] = false;
}


