m/*
 * bucket.h
 *
 *  Created on: 1 dic 2020
 *      Author: vcapo
 */

#ifndef BUCKET_H_
#define BUCKET_H_

#include <iostream>
using namespace std;


template <class K, class V>
class bucket{

	public:
		typedef K chiave;
		typedef V valore;

		bucket(){

			eliminato = false;
		};

		bucket(chiave c, valore v){

			key = c;
			value = v;
			eliminato = false;
		};

		bucket(bucket<K,V>& altro){

			key = altro.key;
			value = altro.value;
			eliminato = false;
		};

		~bucket(){}; //??

		void setChiave(chiave c){

			key = c;
		};

		void setValore(valore v){

			value = v;
		};

		chiave getChiave() const{

			return key;
		};

		valore getValore() const{

			return value;
		};

		bool isEliminato() const{

			return eliminato;
		};

		void setEliminato(bool e){

			eliminato = e;
		};

		friend ostream& operator<<(ostream& os, const bucket& b){
			os << "<" << b.key << ">:<" << b.value << ">";
			return os;
		}

		friend ostream& operator<<(ostream& os, const bucket* b){
			os << "<" << b->key << ">:<" << b->value << ">";
			return os;
		}

	private:
		chiave key;
		valore value;
		bool eliminato;
};


#endif /* BUCKET_H_ */
