/*
 * randomAlg.cpp
 *
 *  Created on: Oct 20, 2014
 *      Author: jacek
 */
#include "../inc/randomAlg.h"

runResult randomAlg(void){
	runResult res;
	res.numberOfSteps = 1;
	res.permutation = generateRandomPermutation();
	res.cost = rateSolution(A, B, permutation, size);
	return res;
}


