/*
 * codap_eccezzioni.h
 *
 *  Created on: 15 dic 2020
 *      Author: vcapo
 */

#ifndef CODAP_ECCEZZIONI_H_
#define CODAP_ECCEZZIONI_H_

struct priorityQueueException{};
struct CodaPiena : public priorityQueueException{};
struct CodaVuota : public priorityQueueException{};

#endif /* CODAP_ECCEZZIONI_H_ */
