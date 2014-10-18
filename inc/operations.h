/*
 * operations.h
 *
 *  Created on: Oct 15, 2014
 */

#ifndef OPERATIONS_H_
#define OPERATIONS_H_

#include <random>

/**
 * Returns pointer to a randomly generated solution based on previous one (int vector).
 * @param solution pointer to the original solution.
 * @param permutation pointer to the space allocated for a permutation.
 * @param sz size of the vector.
 * @param randGen instance of mt19937 random number generator.
 */
int* generateRandomPermutation(int* solution, int* permutation, unsigned int sz, std::mt19937& randGen);

/**
 * Given a solution vector and problem size, returns all 2-opt neighbours.
 * @param solution pointer to the original solution.
 * @param neighbours pointer to space allocated for generated neighbours.
 * @param sz size of the solution vector.
 */
int** generateAllNeighbours(int* solution, int** neighbours, unsigned int sz);

/**
 * Swaps elements in a given solution vector.
 * @param solution pointer to the solution vector to be changed.
 * @param pos1 position of the first element to be swapped.
 * @param pos2 position of the second element to be swapped.
 */
void switchElements(int* solution, unsigned int pos1, unsigned int pos2);


#endif /* OPERATIONS_H_ */
