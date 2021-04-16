/*
 *
 * LAB 9: Realizzazione di albero binario mediante puntatori.
 *
 *
 */

#ifndef ALBERO_BINARIO_P_H_
#define ALBERO_BINARIO_P_H_

#include <iostream>
#include "Albero_binario_astratto.h"

template <class T>
class Albero_binario_p;

template <class T>
class cella{

	friend class Albero_binario_p<T>;
	private:
		cella<T>* genitore;
		cella<T>* sinistro;
		cella<T>* destro;
		T valore;
	public:
	    bool operator==(const cella& rhs)
	    {
	        return (valore == rhs.valore
	            && ((sinistro == 0 && rhs.sinistro == 0)
	                || (sinistro != 0 && rhs.sinistro != 0 && *sinistro == *rhs.sinistro))
	            && ((destro == 0 && rhs.destro == 0)
	                || (destro != 0 && rhs.destro != 0 && *destro == *rhs.destro)));
	    }
};

template <class T>
class Albero_binario_p : public Albero_binario_astratto<T, cella<T>*>{

	public:
		typedef typename Albero_binario_astratto<T, cella<T>*>::tipo tipo;
		typedef typename Albero_binario_astratto<T, cella<T>*>::Nodo Nodo;

		//Costruttore e distruttore
		Albero_binario_p();
		Albero_binario_p(const Albero_binario_p<T>&);
		~Albero_binario_p();

		//Operatori
		void crea();
		bool vuoto() const;
		Nodo radice() const;
		Nodo genitore(Nodo) const;
		Nodo sinistro(Nodo) const;
		Nodo destro(Nodo) const;
		bool sinistro_vuoto(Nodo) const;
		bool destro_vuoto(Nodo) const;
		void cancella(Nodo);
		T leggi(Nodo) const;
		void scrivi(Nodo, tipo);
		void inserire_radice(Nodo);
		void inserire_sinistro(Nodo);
		void inserire_destro(Nodo);

		//altre
		int conta_nodi(Nodo) const;
		//void mutation(Nodo, Albero_binario_p<T>, Nodo); Da fare!!!!

		//Overloading operatori
		Albero_binario_p<T>& operator=(const Albero_binario_p<T>&);
		bool operator==(const Albero_binario_p<T>&); //come funzionaaaa???

	private:
		Nodo copia_sottoalbero(const Nodo&, const Nodo&);
		cella<T>* inizio;
};

template <class T>
Albero_binario_p<T>::Albero_binario_p(){

	crea();
}

template <class T>
Albero_binario_p<T>::Albero_binario_p(const Albero_binario_p<T>& A){

	if(!A.vuoto())
	{
		inizio = copia_sottoalbero(A.radice(), nullptr);
	}
	else
		crea();
}

template <class T>
Albero_binario_p<T>::~Albero_binario_p(){

	cancella(radice());
}

template <class T>
void Albero_binario_p<T>::crea(){

	inizio = nullptr;
}

template <class T>
bool Albero_binario_p<T>::vuoto() const{

	return (inizio == nullptr);
}

template <class T>
typename Albero_binario_p<T>::Nodo Albero_binario_p<T>::radice() const{

	if(!vuoto())
		return inizio;
	else
		return nullptr;

}

template <class T>
typename Albero_binario_p<T>::Nodo Albero_binario_p<T>::genitore(Nodo n) const{

	if(n != nullptr)
	{
		if(n != inizio)
			return n->genitore;
		else
			throw RadiceNonHaPadre();
	}
	else
		throw NodoNullo();
}

template <class T>
typename Albero_binario_p<T>::Nodo Albero_binario_p<T>::sinistro(Nodo n) const{

	if(n != nullptr)
	{
		if(n->sinistro != nullptr)
			return n->sinistro;
		else
			return nullptr;
	}
	else
		throw NodoNullo();


}

template <class T>
typename Albero_binario_p<T>::Nodo Albero_binario_p<T>::destro(Nodo n) const{

	if(n != nullptr)
	{
		if(n->destro != nullptr)
			return n->destro;
		else
			return nullptr;
	}
	else
		throw NodoNullo();
}

template <class T>
bool Albero_binario_p<T>::sinistro_vuoto(Nodo n) const{

	if(n != nullptr)
	{
		bool esito = false;
		if(n->sinistro == nullptr)
			esito = true;
		return esito;
	}
	else
		throw NodoNullo();

}

template <class T>
bool Albero_binario_p<T>::destro_vuoto(Nodo n) const{

	if(n != nullptr)
	{
		bool esito = false;
		if(n->destro == nullptr)
			esito = true;
		return esito;
	}
	else
		throw NodoNullo();
}

template <class T>
void Albero_binario_p<T>::cancella(Nodo n){

	if (!vuoto())
	{
		if(!sinistro_vuoto(n))
		{
			cancella(sinistro(n));
		}
		if(!destro_vuoto(n))
		{
			cancella(destro(n));
		}
		if(n == radice())
		{
			delete n;
			inizio = nullptr;
		}
		else
		{
			if(sinistro(genitore(n)) == n)
			{
				n->genitore->sinistro = nullptr;
				delete n;
			}
			else
			{
				n->genitore->destro = nullptr;
				delete n;
			}
		}
    }
}

template <class T>
T Albero_binario_p<T>::leggi(Nodo n) const{

	if(n != nullptr)
		return n->valore;
	else
		throw NodoNullo();
}

template <class T>
void Albero_binario_p<T>::scrivi(Nodo n, tipo v){

	if(!vuoto())
	{
		if(n != nullptr)
			n->valore = v;
		else
			throw NodoNullo();
	}
	else
		throw AlberoVuoto();
}

template <class T>
void Albero_binario_p<T>::inserire_radice(Nodo n){

	if(vuoto())
	{
		if(n != nullptr)
		{
			inizio = n;
			inizio->destro = nullptr;
			inizio->sinistro = nullptr;
			inizio->genitore = nullptr;
		}
		else
			throw NodoNullo();
	}
	else
		throw RadiceEsiste();
}

template <class T>
void Albero_binario_p<T>::inserire_sinistro(Nodo n){

	if(!vuoto())
	{
		if(sinistro_vuoto(n))
		{
			cella<T>* nuovo = new cella<T>;
			n->sinistro = nuovo;
			n->sinistro->sinistro = nullptr;
			n->sinistro->destro = nullptr;
			n->sinistro->genitore = n;
		}
		else
			throw NodoEsiste();
	}
	else
		throw AlberoVuoto();
}

template <class T>
void Albero_binario_p<T>::inserire_destro(Nodo n){

	if(!vuoto())
	{
		if(destro_vuoto(n))
		{
			cella<T>* nuovo = new cella<T>;
			n->destro = nuovo;
			n->destro->sinistro = nullptr;
			n->destro->destro = nullptr;
			n->destro->genitore = n;
		}
		else
			throw NodoEsiste();
	}else
		throw AlberoVuoto();

}

template <class T>
typename Albero_binario_p<T>::Nodo Albero_binario_p<T>::copia_sottoalbero(const Nodo& n, const Nodo& g){

	if(n != nullptr)
	{
		cella<T>* nuovo = new cella<T>;
		nuovo->valore = n->valore;
		nuovo->genitore = g;
		nuovo->sinistro = nullptr;
		nuovo->destro = nullptr;
		nuovo->sinistro = copia_sottoalbero(n->sinistro, nuovo);
		nuovo->destro = copia_sottoalbero(n->destro, nuovo);
		return nuovo;
	}
	else
		return nullptr;
}

template <class T>
int Albero_binario_p<T>::conta_nodi(Nodo n) const{

	if(n == nullptr)
		return 0;
	else
	{
		int dim_sinistro = conta_nodi(n->sinistro);
		int dim_destro = conta_nodi(n->destro);
		return (dim_sinistro + dim_destro + 1);
	}
}

/******************* Overloading operatori ********************/
//Sembra ok
template<class T>
Albero_binario_p<T>& Albero_binario_p<T>::operator=(const Albero_binario_p<T>& A){

	if (this != &A)
	{
		if(!this->vuoto())
		{
			if(!A.vuoto())
			{
				this->~Albero_binario_p();
				inizio = copia_sottoalbero(A.radice(), nullptr);
			}
			else
			{
				this->~Albero_binario_p();
				this->crea();
			}
		}
		else
		{
			if(!A.vuoto())
				inizio = copia_sottoalbero(A.radice(), nullptr);
		}
	}
	return *this;
}

template<class T>
bool Albero_binario_p<T>::operator==(const Albero_binario_p<T>& A){

	return (radice() == 0 && A.radice() == 0)
	        || (radice() != 0 && A.radice() != 0 && *radice() == *A.radice());
}


#endif /* ALBERO_BINARIO_P_H_ */
