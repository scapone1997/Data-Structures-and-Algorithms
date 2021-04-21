/*
 * Dizionario.h
 *
 *  Created on: 1 dic 2020
 *      Author: vcapo
 */

#ifndef DIZIONARIO_H_
#define DIZIONARIO_H_

#include "bucket.h"


//Classe astratta Dizionario
template <class K, class V>
class Dizionario{

	public:
		typedef K chiave;
		typedef V valore;

		//Metodi
		virtual void crea_dizionario() = 0;
		virtual bool dizionario_vuoto() const = 0;
		virtual bool appartiene(const chiave&) const = 0;
		virtual void inserisci(const chiave&, const valore&) = 0;
		virtual void cancella(const chiave&) = 0;
		virtual bucket<K, V>* recupera(const chiave&) const = 0;

		//funzioni di servizio
		virtual void aggiorna_valore(const chiave&, const valore&) = 0;

		//virtual int dimensioneDizionario() const = 0;
};



#endif /* DIZIONARIO_H_ */
