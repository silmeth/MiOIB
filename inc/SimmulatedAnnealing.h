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
#include <math.h>

// Right, we know there is an error in class' name.
// But we don't give a damn.
class SimmulatedAnnealing: public BaseAlgorithm {
private:
	SimmulatedAnnealing();
    stopCondition cond;
    int stopVal;
    float temperature;
    /**
     * Calculate initial temperature.
     * Give the worst neighbour 95% of chances of choosing.
     */
    float initTemp(unsigned int worstNeighbourCost);
    /**
     * Get highest cost of neighbours.
     */
    unsigned int getWorstNeighbourCost();
    /**
     * Decrease temperature.
     * T(t+1) = T(t) * multiplier
     */
    float decreaseTemperature(float multiplier);
public:
    SimmulatedAnnealing(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed = 19910401);
	virtual ~SimmulatedAnnealing();
	virtual void init(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed = 19910401);
	virtual void clean();
	void run();
	void repeatedRun(unsigned int repetitions);
	float lowestTemperature;
	/**
	 * Generete threshold for accepting solution with given cost.
	 */
	float acceptSolutionThreshold(unsigned int cost);
};

#endif /* SIMMULATEDANNEALING_H_ */
