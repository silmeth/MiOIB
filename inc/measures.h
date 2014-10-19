/*
 * measures.h
 *
 *  Created on: Oct 15, 2014
 */

#ifndef MEASURES_H_
#define MEASURES_H_

/**
 * Returns the cost for given solution vector.
 * @param A matrix with flow values between facilities.
 * @param B matrix with distance values between locations.
 * @param solution pointer to the solution (array of ints).
 * @param sz size of the problem and solution.
 */
int rateSolution(int** A, int** B, int* solution, int sz);

/*
 * Calculates difference in cost function if elements on positions pos1 and pos2 switch places in solution vector
 * pos1, pos2 - position of elements which switch place in graded solution
 * distances - matrix with distances between places
 * flows - matrix with flows values
 */
float rateChange(int *solution, int problemSize, int *distances, int *flows, int pos1, int pos2);

#endif /* MEASURES_H_ */
