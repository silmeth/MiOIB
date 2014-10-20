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
};

extern int** A;
extern int** B;
extern int size;
extern int* permutation;

/*
 * Initialise all data structures.
 */
void algInit(int sz, int** matA, int** matB, int* perm);

void algClear();

#endif /* ALGORITHMS_H_ */
