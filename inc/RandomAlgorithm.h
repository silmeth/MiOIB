/*
 * RandomAlgorithm.h
 *
 *  Created on: Oct 22, 2014
 */

#ifndef RANDOMALGORITHM_H_
#define RANDOMALGORITHM_H_

#include <stdio.h>
#include <string.h>
#include <chrono>

#include "BaseAlgorithm.h"
//#include "operations.h"

class RandomAlgorithm: public BaseAlgorithm {
public:
private:
    RandomAlgorithm();
public:
    RandomAlgorithm(int size, int** matA, int** matB, int seed=19910401);
    virtual ~RandomAlgorithm();
    void run(unsigned int numberOfRuns);
};

#endif /* RANDOMALGORITHM_H_ */
