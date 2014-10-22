/*
 * BaseAlgorithm.h
 *
 *  Created on: Oct 22, 2014
 */

#include <stddef.h>
#include <assert.h>
#include <iostream>

#include "operations.h"

#ifndef BASEALGORITHM_H_
#define BASEALGORITHM_H_

enum stopCondition
{
    definiteNumberOfSteps = 0,
    minimalImprovement = 1
};

struct runResult {
	int problemSize;
	// Cost of the best permutation = solution.
	int cost;
	// Pointer to the best permutation.
	int* bestPermutation;
	/**
	 * Number of steps needed to find solution.
	 * If program is run with definiteNumberOfSteps, step in which the best solution was found is stored here.
	 */
	int numberOfSteps;
	/**
	 * Stores costs of permutation from each step.
	 * Needed for plotting improvement of solution over time.
	 */
	int* historicalCosts;
};

class BaseAlgorithm {
public:
	BaseAlgorithm();
	BaseAlgorithm(int size);
	virtual ~BaseAlgorithm();
public:
	/*
	 * Initialises the algorithm.
	 * Allocates memory and creates a random permutation (start permutation).
	 */
	void init(int size);
	/*
	 * Runs the algorithm.
	 * @param numberOfRuns Number of runs of the algorithm.
	 * @param stopCondition Type of stop condition.
	 * @param value Depending on stop condition either number of steps or minimal improvement.
	 * @return runResult After reaching stop condition it returns a  structure containing all parameters required for futher processing.
	 */
	runResult* run(int numberOfRuns, stopCondition condition, double value);
	/*
	 * Removes unnecesary data structures.
	 */
	void clean();
	/*
	 * Random permutation initialiased in init().
	 */
	int* startPermutation;
	int problemSize;
	runResult* result;
private:
	/*
	 * Starts time measurement.
	 */
	void startTime();
	/*
	 * Stops time measurement.
	 * @return Time in seconds elapsed from startTime().
	 */
	double stopTime();

};

#endif /* BASEALGORITHM_H_ */
