/*
 * algorithms.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: jacek
 */

#include "../inc/algorithms.h"

int** A;
int** B;
int size;
int* algPermutation;

void algInit(int sz, int** matA, int** matB, int* perm){
	size = sz;
	A = matA;
	B = matB;
	algPermutation = perm;
}


