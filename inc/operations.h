/*
 * operations.h
 *
 *  Created on: Oct 15, 2014
 */

#ifndef OPERATIONS_H_
#define OPERATIONS_H_

/*
 * Returns pointer to a randomly generated solution (int vector)
 */
int* generateRandomPermutation(int size);

/*
 * Given a solution vector and problem size, returns all 2-opt neighbours.
 */
int** generateAllNeighbours(int* solution, int size);

/*
 * Switches elements in solution vector.
 */
void switchElements(int* solution, int pos1, int pos2);


#endif /* OPERATIONS_H_ */
