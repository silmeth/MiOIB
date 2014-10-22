/*
 * operations.h
 *
 *  Created on: Oct 15, 2014
 */

#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#include <random>

/**
 * Initializes all needed values to work on solutions. Calculates size of neighbourhood, creates random
 * number generator, allocates memory for all needed arrays.
 * @param size size of the problem (and its solution).
 * @param seed seed for uniform Marsenne Twister 19937 random generator, defaults to 19910401.
 */
void opInit(unsigned int size, int seed = 19910401);

/**
 * Returns pointer to a randomly generated solution based on previous one (array of ints).
 * @return pointer to array of ints with random solution generated.
 */
unsigned int* generateRandomPermutation();

/**
 * Given a solution vector and problem size, returns all 2-opt neighbours.
 * @param solution pointer to the original solution (array of ints).
 * @return pointer to array of arrays with all 2-opt neighbours of the solution.
 */
unsigned int** generateAllNeighbours(unsigned int* solution);

/**
 * Find numbers of elements to swap in order to generate i-th neighbour of a solution.
 * @param i Number of the neighbour.
 * @return Array int[2] with numbers of elements swapped to generate i-th neighbour.
 */
unsigned int* getNeighbourSwaps(unsigned int i);

/**
 * Swaps elements in a given solution vector.
 * @param solution pointer to the solution to be changed (array of ints).
 * @param pos1 position of the first element to be swapped.
 * @param pos2 position of the second element to be swapped.
 */
void switchElements(unsigned int* solution, unsigned int pos1, unsigned int pos2);

/**
 * Deallocates all previously allocated data
 */
void opClear();


#endif /* OPERATIONS_H_ */
