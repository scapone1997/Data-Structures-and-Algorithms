/*
 * eccezioni_dizionario.h
 *
 *  Created on: 1 dic 2020
 *      Author: vcapo
 */


struct dictionaryException { };
struct DizionarioPieno : public dictionaryException { };
struct DizionarioVuoto : public dictionaryException { };
struct ChiaveNonEsiste : public dictionaryException { };
