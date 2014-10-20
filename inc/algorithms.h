/*
 * algorithms.h
 *
 *  Created on: Oct 15, 2014
 *
 *
 */

#ifndef ALGORITHMS_H_
#define ALGORITHMS_H_

// TODO Figure out input arguments and output values.
// TODO Where should we measure time? Inside algorithm functions?

/*
 * Runs random algorithm.
 * Returns solution, cost.
 */
void randomAlg();
/*
 * Runs heuristic algorithm.
 * Returns solution, cost.
 */
void heuristicAlg();
/*
 * Runs Greedy Search Algorithm.
 * Returns solution, cost, number of steps.
 */
void greedyAlg();
/*
 * Runs Steepest Search Algorithm.
 * Returns solution, cost, number of steps.
 */
void steepestAlg();
/*
 * Prints results to python-readable format.
 */
void printResults();


#endif /* ALGORITHMS_H_ */
