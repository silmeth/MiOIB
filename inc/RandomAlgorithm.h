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

class RandomAlgorithm: public BaseAlgorithm {
private:
    RandomAlgorithm();
public:
    RandomAlgorithm(unsigned int size, int** matA, int** matB, unsigned int numberOfRuns, int seed=19910401);
    virtual void init(unsigned int size, int** matA, int** matB, unsigned int numberOfRuns, int seed=19910401);
    virtual void clean();
    virtual ~RandomAlgorithm();
    void run();
};

#endif /* RANDOMALGORITHM_H_ */
