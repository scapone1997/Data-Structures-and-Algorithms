/*
 * hash.h
 *
 *  Created on: 1 dic 2020
 *      Author: vcapo
 */

#ifndef HASH_H_
#define HASH_H_

#include <iostream>
#include <typeinfo>
#include <string>
using namespace std;


//Funzioni di Hash
template <class T>
class hashClass{
   public:
		size_t operator() (const T key) const;
};


//Restituisce il float
template<>
class hashClass<float>{
	public:
		size_t operator()(const float key) const{
			return key;
		}
};


//Restituisce l'intero
template<>
class hashClass<int>{
	public:
		size_t operator()(const int key) const{
			return key;
		}
};


//Converte un carattere in un numero intero e restituisce il risultato
template<>
class hashClass<char>{
	public:
		size_t operator()(const char key) const{
			unsigned long valore_hash = 1;
			valore_hash = 31 * valore_hash + key;
			return size_t(valore_hash);
		}
};


//Converte una parola nel rispettivo numero intero e restituisce il risultato
template <>
class hashClass<string>{
	public:
	size_t operator()(const string key) const {
		unsigned long valore_hash = 0;
		int lunghezza = (int)key.length();
		for (int i=0; i<lunghezza; i++)
			valore_hash = 31 * valore_hash + key.at(i);
		return size_t(valore_hash);
	}
};


#endif /* HASH_H_ */




