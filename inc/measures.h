/*
 * measures.h
 *
 *  Created on: Oct 15, 2014
 */

#ifndef MEASURES_H_
#define MEASURES_H_

float gradeSolution(int *solution, int problemSize, int *distances, int *flows);
/*
 * Calculate difference in cost function if elements on positions pos1 and pos2 switch places
 */
float gradeChange(int *solution, int problemSize, int *distances, int *flows, int pos1, int pos2);

#endif /* MEASURES_H_ */
