/*
 * BaseAlgorithm.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: jacek
 */

#include "../inc/BaseAlgorithm.h"

BaseAlgorithm::BaseAlgorithm() {
	this->startPermutation = NULL;
	this->problemSize = 0;
	this->result = NULL;
}

BaseAlgorithm::BaseAlgorithm(int size){
	assert(size > 0);
	this->problemSize = size;

	// TODO If seed not set in operations, set it here.
	opInit(this->problemSize);
	this->startPermutation = generateRandomPermutation();

	this->result = new runResult;
}

BaseAlgorithm::~BaseAlgorithm() {
	this->clean();
}

void BaseAlgorithm::init(int size){
	assert(size > 0);
	this->problemSize = size;

	// TODO If seed not set in operations, set it here.
	opInit(this->problemSize);
	this->startPermutation = generateRandomPermutation();

	this->result = new runResult;
}

/*
 * TODO Implement measuring time.
 */

void BaseAlgorithm::startTime(){
}

double BaseAlgorithm::stopTime(){
	return 0.0;
}

void BaseAlgorithm::clean(){
	if(this->result != NULL) {
		delete [] this->result->bestPermutation;
		delete [] this->result->historicalCosts;
		delete this->result;
		this->result = NULL;
	}
	if(this->startPermutation != NULL) {
		delete [] this->startPermutation;
		this->startPermutation = NULL;
	}
}


