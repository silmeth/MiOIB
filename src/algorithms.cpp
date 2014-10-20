/*
 * algorithms.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: jacek
 */

#include "../inc/algorithms.h"

int** A;
int** B;
int sz;
int* permutation;

void algInit(int size, int** matA, int** matB, int* perm){
	sz = size;
	A = matA;
	B = matB;
	permutation = perm;
}

void algClear(){
	delete permutation;
	delete []A;
	delete []B;
}

