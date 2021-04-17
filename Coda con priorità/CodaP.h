/*
 * CodaP.h
 *
 *  Created on: 15 dic 2020
 *      Author: vcapo
 */

#ifndef CODAP_H_
#define CODAP_H_

#include <iostream>
#include "codap_eccezzioni.h"

template <class T>
class CodaP{

	public:
 		typedef T tipo;

 		//Metodi
  		CodaP();
  		CodaP(int);
  		~CodaP();
 		void crea_priori_coda();
  		void inserisci(tipo);
  		tipo min();
  		void cancella_min();
  		void cambia_min(const tipo&); //Lab
  		void rimuovi(const tipo&); //Lab
  		tipo max(); //Lab

  		friend std::ostream& operator<<(std::ostream& os, const CodaP<T>& C)
  		{
  			os << "[";
  			for(int i=0; i<C.ultimo; i++){
  				os << C.heap[i];
  				os << ", ";
  			}
  			os << "]";
  			return os;
  		}

	private:
		int MAX;
  		tipo *heap;
  		int ultimo;
  		void fix_up();
  		void fix_down(int, int);
  		void heapify(tipo arr[], int n, int i); //Converte vettore heap in un max_heap
};


template <class T>
CodaP<T>::CodaP(){

	MAX = 100;
	heap = new tipo[MAX];
 	crea_priori_coda();
};


template <class T>
CodaP<T>::CodaP(int m){

	MAX = m;
	heap = new tipo[MAX];
	crea_priori_coda();
};


template <class T>
CodaP <T>::~CodaP(){

	delete[] heap;
};


template <class T>
void CodaP<T>::crea_priori_coda(){

	ultimo = 0;
};


template <class T>
void CodaP<T>::inserisci(tipo e){

	if(ultimo < MAX)
	{
		ultimo++;
		heap[ultimo-1] = e;
		fix_up();
	}
	else
		throw CodaPiena();
};


template <class T>
typename CodaP<T>::tipo CodaP<T>::min(){

	if(ultimo != 0)
		return(heap[0]);
	else
		throw CodaVuota();

};


template <class T>
void CodaP<T>::cancella_min(){

	if(ultimo != 0)
	{
		heap[0] = heap[ultimo-1];
		ultimo--;
	  	fix_down(1, ultimo);
	}
	else
		throw CodaVuota();
};


/* Per ripristinare i vincoli dell' heap quando la priorità di un nodo è      *
 * cresciuta, ci spostiamo nell' heap verso l'alto, scambiando, se necessario,*
 * il nodo in posizione k con il suo nodo padre (in posizione k/2),           *
 * continuando fintanto che heap[k]<heap[k/2] oppure fino a quando            *
 * raggiungiamo la cima dell' heap.                                           */
template <class T>
void CodaP<T>::fix_up(){

	int k = ultimo;
  	while(k>1 && heap[k-1] < heap[k/2-1]){
      	tipo tmp = heap[k-1];
     	heap[k-1] = heap[k/2-1];
     	heap[k/2-1] = tmp;
      	k = k/2;
    }
}


/* Per ripristinare i vincoli dell' heap quando la priorità di un nodo si è   *
 * ridotta, ci spostiamo nell' heap verso il basso, scambiando, se necessario,*
 * il nodo in posizione k con il minore dei suoi nodi figli e arrestandoci    *
 * quando il nodo al posto k non è più grande di almeno uno dei suoi figli    *
 * oppure quando raggiungiamo il fondo dell' heap. Si noti che se N è pari e  *
 * k è N/2, allora il nodo in posizione k ha un solo figlio: questo caso      *
 * particolare deve essere trattato in modo appropriato.                      */
template <class T>
void CodaP<T>::fix_down(int k, int N){

	short int scambio = 1;
	while (k<=N/2 && scambio)
	{
      	int j = 2*k;
      	if(j<N && heap[j-1] > heap[j])
      		j++;
      	scambio = heap[j-1];
      	if(scambio < heap[k-1])
		{
			tipo tmp = heap[k-1];
			heap[k-1] = heap[j-1];
			heap[j-1] = tmp;
			k = j;
		}
  	}
}


template <class T>
void CodaP<T>::cambia_min(const tipo& e){

	if(e < min())
		heap[0] = e;
}


template <class T>
void CodaP<T>::rimuovi(const tipo& e){

	bool esiste = false;
	int p; //posizione dell'elemento e
	for(int i = 0; i < ultimo; i++)
	{
		if(heap[i] == e)
		{
			esiste = true;
			p = i;
		}
	}
	if(esiste == true)
	{
		for(int j = p; j<ultimo-1; j++)
			heap[j] = heap[j+1];
		ultimo--;
	}
}


template <class T>
typename CodaP<T>::tipo CodaP<T>::max(){

	//Copio il vettore heap
	tipo* copia = new tipo[MAX];
	for(int i = 0; i < ultimo; i++)
		copia[i] = heap[i];
	int start = ((ultimo)/2)-1;

	// Perform reverse level order traversal
	// from last non-leaf node and heapify
	// each node
	for(int i = start; i >= 0; i--)
	      heapify(copia, ultimo, i);
	return copia[0];
}


//Trasforma un vettore generico in un max_heap
template <class T>
void CodaP<T>::heapify(tipo arr[], int n, int i)
{
    int max = i; // Inizializzo come radice
    int l = 2*i+1; // sinistro = 2*i + 1
    int r = 2*i+2; // destro = 2*i + 2

    //Se il figlio sinistro è più grande della radice
    if (l < n && arr[l] > arr[max])
        max = l;

    //Se il figlio destro è più grande del fratello sinistro
    if (r < n && arr[r] > arr[max])
        max = r;

    //Se la radice non è il più grande
    if (max != i)
    {
    	tipo tmp = arr[i];
    	arr[i] = arr[max];
    	arr[max] = tmp;

        // Chiamo heapify ricorsivamente sul sottoalbero
        heapify(arr, n, max);
    }
}


#endif /* CODAP_H_ */
