/*
 * albero_eccezioni.h
 *
 *  Created on: 10 dic 2020
 *      Author: vcapo
 */

#ifndef ALBERO_ECCEZIONI_H_
#define ALBERO_ECCEZIONI_H_

#include <stdexcept>

struct NodoNullo : public std::invalid_argument {
    NodoNullo() : invalid_argument(
        "Parametro nodo nullo.") {};
};

struct RadiceNonHaPadre : public std::domain_error {
	RadiceNonHaPadre() : domain_error(
        "Il parametro radice non ha genitore.") {};
};

struct RadiceNonHaFratelli : public std::domain_error {
	RadiceNonHaFratelli() : domain_error(
        "Il parametro radice non ha fratelli.") {};
};

struct RadiceEsiste : public std::domain_error {
    RadiceEsiste() : domain_error(
        "Radice gia' presente.") {};
};

struct AlberoVuoto : public std::domain_error {
    AlberoVuoto() : domain_error(
        "Albero vuoto.") {};
};

struct NodoEsiste : public std::domain_error {
    NodoEsiste() : domain_error(
        "Nodo gia' presente.") {};
};

struct QuestoNodoNonHaFigli : public std::domain_error {
	QuestoNodoNonHaFigli() : domain_error(
        "Questo nodo non ha figli.") {};
};

struct QuestoNodoNonHaFratelli : public std::domain_error {
	QuestoNodoNonHaFratelli() : domain_error(
        "Questo nodo non ha fratelli.") {};
};

#endif /* ALBERO_ECCEZIONI_H_ */
