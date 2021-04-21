/*
 * hashAperto.h
 *
 *  Created on: 1 dic 2020
 *      Author: vcapo
 */

#ifndef HASHCHIUSO_H_
#define HASHCHIUSO_H_

#include <iostream>
#include <string>
#include "bucket.h" //Ok
#include "hash.h" //Ok
#include "eccezioni_dizionario.h" // Ok
#include "Lista.h"
#include "Dizionario.h" //Ok
using namespace std;


template <class K, class V>
class Dictionary : public Dizionario<K,V>{

	public:
		typedef typename Dizionario<K,V>::chiave chiave;
		typedef typename Dizionario<K,V>::valore valore;

		Dictionary();
		Dictionary(int);
		~Dictionary();

		void crea_dizionario();
		bool dizionario_vuoto() const;
		bool appartiene(const chiave&) const;
		void inserisci(const chiave& c, const valore& v);
		void cancella(const chiave&);
		bucket<K, V>* recupera(const chiave&) const;
		int scansiona(const chiave&) const;
		void aggiorna_valore(const chiave&, const valore&);
		bool contains_value(const valore&);
		Lista<V> values();
		Lista<K> keys();
		void resize(); //Lab

		//Overloading <<
		friend ostream& operator<<(ostream& os, const Dictionary<K,V>& d)
		{
			if(!d.dizionario_vuoto()){
				os << "[Dizionario]: ";
				os << d.dimensione;
				os << endl;
				for (int i = 0; i<d.dimensione; i++)
				{
					if ((d.table[i] == NULL))
					{
						os << "\t[" << i << "]\t->\tVuoto";
						os << endl;
					}
					else
						{
							if (d.table[i]->isEliminato()){
								os << "\t[" << i << "]\t->\tEliminato";
								os << endl;
						}
						else
							{
								os << "\t[" << i << "]\t->\t" << d.table[i];
								os << endl;
							}
					}
				}
			}
			else os << "ATTENZIONE: Il Dizionario e' vuoto!" << endl;
			return os ;
		}

	private:
		bucket<K,V>** table;
		hashClass<K> hashMap;
		int dimensione;
		int lunghezza;
};


template <class K, class V>
Dictionary<K,V>::Dictionary(){

	dimensione = 50;
	lunghezza = 0;
	crea_dizionario();
}


template <class K, class V>
Dictionary<K,V>::Dictionary(int dim){

	dimensione = dim;
	lunghezza = 0;
	crea_dizionario();
}


template <class K, class V>
Dictionary<K,V>::~Dictionary(){

	delete[] table;
}


template <class K, class V>
void Dictionary<K,V>::crea_dizionario(){

	table = new bucket<K,V>*[dimensione];
	for (int i = 0; i < dimensione; i++)
		table[i] = NULL;
}


template <class K, class V>
bool Dictionary<K,V>::dizionario_vuoto() const{

	return (lunghezza == 0);
}


//Data una chiave c, ci dice se table[c] � occupata o meno
template <class K, class V>
bool Dictionary<K,V>::appartiene(const chiave& c) const{

	return (recupera(c) != NULL);
}


/*
 * Convertiamo la chiave c in intero.
 * Se c � gi� occupata allora modificiamo il suo valore con quello ricevuto in input.
 * Inoltre, se la posizione c � una posizione eliminata, settiamo eliminato di nuovo
 * a false.
 *
 * Se c non � occupata, creiamo un nuovo bucket con i valori ricevuti in input.
 */
template <class K, class V>
void Dictionary<K,V>::inserisci(const chiave& c, const valore& v){

	if (lunghezza < dimensione)
	{
		int p = scansiona(c);
		if(appartiene(c))
		{
			table[p]->setValore(v);
			if (table[p]->isEliminato())
			{
				table[p]->setEliminato(false);
				lunghezza++;
			}
		}
		else
		{
			table[p] = new bucket<K,V>(c, v);
			lunghezza++;
		}
	}
	else
		throw DizionarioPieno();
}

/*
 * Se la chiave c � occupata, recuperiamo il bucket corrispondente e settiamo
 * il campo eliminato a true.
 */
template <class K, class V>
void Dictionary<K,V>::cancella(const chiave& c){

	if(!dizionario_vuoto())
	{
		if(appartiene(c))
		{
			recupera(c)->setEliminato(true);
			lunghezza--;
		}
	}
	else
		throw DizionarioVuoto();
}

/*
 * Convertiamo la chiave c in un intero p;
 * Se table[p] � nulla o occupata proprio da c allora restituiamo
 * il bucket <c, v> corrispondente. Altrimenti restituiamo NULL.
 */
template <class K, class V>
bucket<K, V>* Dictionary<K,V>::recupera(const chiave& c) const{

	int p = scansiona(c);
	if (table[p] == NULL || table[p]->getChiave() != c)
		return NULL;
	else
		return table[p];
}

//Data una chiave c, aggiorna il suo valore se presente nel dizionario.
template <class K, class V>
void Dictionary<K,V>::aggiorna_valore(const chiave& c, const valore& v){

	if (recupera(c) != nullptr)
		recupera(c)->setValore(v);
	else throw ChiaveNonEsiste();
}

/*
 * Data una chiave c, ritorniamo (c % mod. dimensione) se table[c] == NULL
 * OPPURE se table[c] == c;
 * Altrimenti, scansioniamo tutto il dizionario fintanto che non troviamo una posizione
 * che rispetta la condizione dell'if.
 *
 * Quindi se la nostra chiave � di tipo "string", ci permette di trovare una posizione
 * libera di tipo intero corrispondente e ci permette anche di ritrovare la posizione.
 *
 */
template <class K, class V>
int Dictionary<K,V>::scansiona(const chiave& c) const{

	int i = (int)hashMap(c) % dimensione;
	int j = i;

	do
	{
		if(table[j] == NULL || table[j]->getChiave() == c)
			return j;
		j = (j+1) % dimensione;// scansione lineare
	}
	while(i != j);

	return j;
}

//Data un valore e, ci dice se esso esiste nel dizionario
template <class K, class V>
bool Dictionary<K,V>::contains_value(const valore& e){

	bool esito = false;
	for(int i = 0; i < dimensione && esito == false; i++)
		if(table[i] != NULL && table[i]->getValore() == e)
			esito = true;
	return esito;
}

//Restituisce la lista dei valori presenti nel dizionario
template <class K, class V>
Lista<V> Dictionary<K,V>::values(){

	Lista<V> L;
	for(int i = 0; i < dimensione; i++)
		if(table[i] != NULL && table[i]->isEliminato() == false)
			L.inserireLista(table[i]->getValore(), L.primoLista());
	return L;
}

//Restituisce la lista delle chiavi presenti nel dizionario
template <class K, class V>
Lista<K> Dictionary<K,V>::keys(){

	Lista<K> L;
	for(int i = 0; i < dimensione; i++)
		if(table[i] != NULL && table[i]->isEliminato() == false)
			L.inserireLista(table[i]->getChiave(), L.primoLista());
	return L;
}

//Raddoppia la dimensione del Dizinario ricopiando tutti i valori memorizzati
template <class K, class V>
void Dictionary<K,V>::resize(){

	bucket<K,V>** old_table = table;
	dimensione = dimensione * 2;
	crea_dizionario();
	for(int i = 0; i< dimensione/2; i++)
		if(old_table[i] != NULL)
			inserisci(old_table[i]->getChiave(), old_table[i]->getValore());
	delete[] old_table;
}

#endif /* HASHCHIUSO_H_ */
