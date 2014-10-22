/*
 * HeuristicAlgorithm.h
 *
 *  Created on: Oct 22, 2014
 *      Author: jacek
 */

#ifndef HEURISTICALGORITHM_H_
#define HEURISTICALGORITHM_H_

#include <stddef.h>
#include <chrono>

#include "BaseAlgorithm.h"

class HeuristicAlgorithm: public BaseAlgorithm {
public:
	HeuristicAlgorithm();
	virtual ~HeuristicAlgorithm();
public:
	void run();
};

#endif /* HEURISTICALGORITHM_H_ */
