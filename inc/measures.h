/*
 * measures.h
 *
 *  Created on: Oct 15, 2014
 */

#ifndef MEASURES_H_
#define MEASURES_H_

/*
 * Returns the cost of solution vector.
 * distances - matrix with distances between places
 * flows - matrix with flows values
 */
float gradeSolution(int *solution, int problemSize, int *distances, int *flows);

/*
 * Calculates difference in cost function if elements on positions pos1 and pos2 switch places in solution vector
 * pos1, pos2 - position of elements which switch place in graded solution
 * distances - matrix with distances between places
 * flows - matrix with flows values
 */
float gradeChange(int *solution, int problemSize, int *distances, int *flows, int pos1, int pos2);

#endif /* MEASURES_H_ */
