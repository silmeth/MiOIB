/*
 * GreedyAlgorithm.h
 *
 *  Created on: 29.10.2014
 */

#ifndef GREEDYALGORITHM_H_
#define GREEDYALGORITHM_H_

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "BaseAlgorithm.h"

class GreedyAlgorithm: public BaseAlgorithm {
private:
    GreedyAlgorithm();
    stopCondition cond;
    int stopVal;
public:
    GreedyAlgorithm(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed = 19910401);
    virtual void init(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed = 19910401);
    virtual ~GreedyAlgorithm();
    virtual void clean();
    void run();
    void repeatedRun(unsigned int repetitions);
};

#endif /* GREEDYALGORITHM_H_ */
