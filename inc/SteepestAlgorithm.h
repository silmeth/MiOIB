/*
 * SteepestAlgorithm.h
 *
 *  Created on: Oct 22, 2014
 *      Author: jacek
 */

#ifndef STEEPESTALGORITHM_H_
#define STEEPESTALGORITHM_H_

#include <iostream>

#include "BaseAlgorithm.h"
#include "operations.h"
#include "measures.h"
#include <stdio.h>
#include <string.h>


class SteepestAlgorithm: public BaseAlgorithm {
public:
	SteepestAlgorithm();
	virtual ~SteepestAlgorithm();
public:
	void run(stopCondition condition, double value);
	void repeatedRun(unsigned int repetitions, stopCondition condition, double value);
	//TODO remove this awful copy
	unsigned int rateSolution2(int** A, int** B, unsigned int* solution, unsigned int sz);
};

#endif /* STEEPESTALGORITHM_H_ */
