/*
 * measures.h
 *
 *  Created on: Oct 15, 2014
 */

#ifndef MEASURES_H_
#define MEASURES_H_

/**
 * Returns the cost for given solution vector. It makes \f$n^2\f$ multiplications.
 * @param A Matrix with flow values between facilities.
 * @param B Matrix with distance values between locations.
 * @param solution Pointer to the solution (array of ints).
 * @param sz Size of the problem and solution.
 * @return Integer value with cost.
 */
int rateSolution(int** A, int** B, int* solution, unsigned int sz);

/**
 * Returns the difference in cost function if elements on positions pos1 and pos2 switch places in given solution vector.
 * It makes \f$8n\f$ multiplications.
 * @param A Matrix with flow values between facilities.
 * @param B Matrix with distance values between locations.
 * @param solution Pointer to the @b original (i.e. previous) solution (array of ints).
 * @param sz Size of the problem and solution.
 * @param pos1 Position of the first element to be swapped.
 * @param pos2 Position of the second element to be swapped.
 */
int rateChange(int** A, int** B, int* solution, unsigned int sz, unsigned int pos1, unsigned int pos2);

#endif /* MEASURES_H_ */
