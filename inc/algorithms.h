/*
 * algorithms.h
 *
 *  Created on: Oct 15, 2014
 *
 *
 */

#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_

#include "../inc/operations.h"
#include "../inc/measures.h"

// TODO Where should we measure time? Inside algorithm functions?

struct runResult{
	int cost;
	int* permutation;
	int numberOfSteps;
	double workTime;
};

int** A;
int** B;
int sz;
int* permutation;

/*
 * Initialise all data structures.
 */
void algInit(int size, int** matA, int** matB, int* permutation);

/*
 * Runs random algorithm.
 * Returns solution, cost.
 */
runResult randomAlg();

/*
 * Runs heuristic algorithm.
 * Returns solution, cost.
 */

runResult heuristicAlg();
/*
 * Runs Greedy Search Algorithm.
 * Returns solution, cost, number of steps.
 */

runResult greedyAlg();
/*
 * Runs Steepest Search Algorithm.
 * Returns solution, cost, number of steps.
 */

runResult steepestAlg();
/*
 * Prints results to python-readable format.
 */

void printResults();


#endif /* ALGORITHMS_H_ */
