/*
 * BaseAlgorithm.h
 *
 *  Created on: Oct 22, 2014
 */

#ifndef BASEALGORITHM_H_
#define BASEALGORITHM_H_

#include <stddef.h>
#include <assert.h>
#include <iostream>
#include <chrono>

#include "operations.h"

enum stopCondition
{
    definiteNumberOfSteps = 0,
    minimalImprovement = 1
};

struct runResult {
	unsigned int problemSize;
	// Cost of the best permutation = solution.
	unsigned int cost;
	// Pointer to the best permutation.
	unsigned int* bestPermutation;
	// Pointer to last permutation
	unsigned int* lastPermutation;
	/**
	 * Number of steps needed to find solution.
	 * If program is run with definiteNumberOfSteps, step in which the best solution was found is stored here.
	 */
	unsigned int numberOfSteps;
	/**
	 * Stores costs of permutation from each step.
	 * Needed for plotting improvement of solution over time.
	 */
	unsigned int* historicalCosts;
	// Time needed to get solution
	double workTime;
};

class BaseAlgorithm {
public:
	BaseAlgorithm();
	BaseAlgorithm(int size, int** matA, int** matB);
	virtual ~BaseAlgorithm();
public:
	/*
	 * Initialises the algorithm.
	 * Allocates memory and creates a random permutation (start permutation).
	 */
	void init(int size, int** matA, int** matB);
	/*
	 * Runs the algorithm.
	 * @param numberOfRuns Number of runs of the algorithm.
	 * @param stopCondition Type of stop condition.
	 * @param value Depending on stop condition either number of steps or minimal improvement.
	 * @return runResult After reaching stop condition it returns a  structure containing all parameters required for futher processing.
	 */
	void run(int numberOfRuns, stopCondition condition, double value);
	/*
	 * Removes unnecesary data structures.
	 */
	void clean();
	/*
	 * Calculates cost for current result->bestPermutation and stores it in result->cost
	 */
	void rateSolution();
	/*
	 * Random permutation initialiased in init().
	 */
	unsigned int problemSize;
	runResult* result;
	int** A;
	int** B;
	bool isInitialised;
};

#endif /* BASEALGORITHM_H_ */
