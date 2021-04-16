/*
 * eccezioni_coda.h
 *
 *  Created on: 21 dic 2020
 *      Author: vcapo
 */

#ifndef ECCEZIONI_CODA_H_
#define ECCEZIONI_CODA_H_

struct codaException{};
struct CodaVuota : public codaException {};
struct CodaPiena : public codaException {};

#endif /* ECCEZIONI_CODA_H_ */
