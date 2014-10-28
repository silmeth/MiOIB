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
private:
    HeuristicAlgorithm();
public:
    HeuristicAlgorithm(int size, int** matA, int** matB, int seed=19910401);
    virtual ~HeuristicAlgorithm();
public:
    void run();
};

#endif /* HEURISTICALGORITHM_H_ */
