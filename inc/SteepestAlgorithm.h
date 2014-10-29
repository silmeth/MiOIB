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
#include <stdio.h>
#include <string.h>

class SteepestAlgorithm: public BaseAlgorithm {
private:
    SteepestAlgorithm();
    stopCondition cond;
    int stopVal;
public:
    SteepestAlgorithm(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed = 19910401);
    virtual void init(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed = 19910401);
    virtual ~SteepestAlgorithm();
    virtual void clean();
    void run();
    void repeatedRun(unsigned int repetitions);
};

#endif /* STEEPESTALGORITHM_H_ */
