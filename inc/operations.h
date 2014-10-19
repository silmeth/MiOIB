/*
 * operations.h
 *
 *  Created on: Oct 15, 2014
 */

#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#include <random>

/**
 * Initializes all needed values to work on solutions
 * @param size size of the problem (and its solution)
 * @param seed seed for uniform Marsenne Twister 19937 random generator, defaults to 19910401
 */
void opInit(unsigned int size, int seed = 19910401);

/**
 * Returns pointer to a randomly generated solution based on previous one (array of ints).
 * @param solution pointer to the original solution.
 * @param permutation pointer to the space allocated for a permutation.
 * @param sz size of the vector.
 * @param randGen instance of mt19937 random number generator.
 */
int* generateRandomPermutation(int* solution);

/**
 * Given a solution vector and problem size, returns all 2-opt neighbours.
 * @param solution pointer to the original solution (array of ints).
 * @param neighbours pointer to space allocated for generated neighbours.
 * @param sz size of the solution vector.
 */
int** generateAllNeighbours(int* solution);

/**
 * Swaps elements in a given solution vector.
 * @param solution pointer to the solution to be changed (array of ints).
 * @param pos1 position of the first element to be swapped.
 * @param pos2 position of the second element to be swapped.
 */
void switchElements(int* solution, unsigned int pos1, unsigned int pos2);

/**
 * Deallocates all previously allocated data
 */
void opClear();


#endif /* OPERATIONS_H_ */
