/*
 * BaseAlgorithm.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: jacek
 */

#include "../inc/BaseAlgorithm.h"

BaseAlgorithm::BaseAlgorithm() {
	this->problemSize = 0;
	this->result = NULL;
	this->isInitialised = false;
	this->A = NULL;
	this->B = NULL;
}

BaseAlgorithm::BaseAlgorithm(int size, int** matA, int** matB) {
	assert(size > 0);
	this->problemSize = size;
	assert(matA != NULL);
	assert(matB != NULL);
	this->A = matA;
	this->B = matB;
	// TODO If seed not set in operations, set it here.
	opInit(this->problemSize);
	this->result = new runResult;
	this->result->bestPermutation = generateRandomPermutation();
	this->result->lastPermutation = generateRandomPermutation();
	this->isInitialised = true;
}

BaseAlgorithm::~BaseAlgorithm() {
	this->clean();
}

void BaseAlgorithm::init(int size, int** matA, int** matB) {
	assert(size > 0);
	this->problemSize = size;
	assert(matA != NULL);
	assert(matB != NULL);
	this->A = matA;
	this->B = matB;
	// TODO If seed not set in operations, set it here.
	opInit(this->problemSize);
	this->result = new runResult;
	this->result->bestPermutation = generateRandomPermutation();
	this->result->lastPermutation = generateRandomPermutation();
	this->isInitialised = true;
}

/*
 * TODO Implement measuring time.
 */

void BaseAlgorithm::startTime() {
}

void BaseAlgorithm::stopTime() {
	this->result->workTime = 1.0;
}

void BaseAlgorithm::clean(){
	if(this->result != NULL) {
		if(this->result->historicalCosts != NULL) {
			delete [] this->result->historicalCosts;
		}
		delete [] this->result->bestPermutation;
		delete this->result;
		this->result = NULL;
	}
	this->isInitialised = false;
}

void BaseAlgorithm::rateSolution() {
	this->result->cost = 0;
	for(unsigned int i = 0; i < this->problemSize; i++) {
		for(unsigned int j = 0; j < this->problemSize; j++) {
			this->result->cost += this->A[i][j]*this->B[this->result->lastPermutation[i]][this->result->lastPermutation[j]];
		}
	}
}

