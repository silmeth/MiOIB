/*
 * SimmulatedAnnealing.h
 *
 *  Created on: 22.11.2014
 */

#ifndef SIMMULATEDANNEALING_H_
#define SIMMULATEDANNEALING_H_

#include "BaseAlgorithm.h"
#include <cstdio>
#include <cstring>
#include <iostream>

class SimmulatedAnnealing: public BaseAlgorithm {
private:
	SimmulatedAnnealing();
    stopCondition cond;
    int stopVal;
public:
    SimmulatedAnnealing(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed = 19910401);
	virtual ~SimmulatedAnnealing();
	virtual void init(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed = 19910401);
	virtual void clean();
	void run();
	void repeatedRun(unsigned int repetitions);
};

#endif /* SIMMULATEDANNEALING_H_ */
