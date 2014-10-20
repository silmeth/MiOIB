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
int* permutation;

void algInit(int sz, int** matA, int** matB, int* perm){
	size = sz;
	A = matA;
	B = matB;
	permutation = perm;
}

void algClear(){
	delete permutation;
	delete []A;
	delete []B;
}

