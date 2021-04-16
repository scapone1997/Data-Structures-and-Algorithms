/*
 * eccezioni.h
 *
 *  Created on: 26 nov 2020
 *      Author: vcapo
 */

#ifndef ALBEROBINARIO_ECCEZIONI_H_
#define ALBEROBINARIO_ECCEZIONI_H_

#include <stdexcept>

struct NodoNullo : public std::invalid_argument {
    NodoNullo() : invalid_argument(
        "Parametro nodo nullo.") {};
};

struct AlberoPieno : public std::invalid_argument {
    AlberoPieno() : invalid_argument(
        "Dimensione massima raggiunta.") {};
};

struct RadiceNonHaPadre : public std::invalid_argument {
	RadiceNonHaPadre() : invalid_argument(
        "Il parametro radice non ha genitore.") {};
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

#endif /* ALBEROBINARIO_ECCEZIONI_H_ */
