/*
 * RandomAlgorithm.cpp
 *
 *  Created on: Oct 22, 2014
 */

#include "../inc/RandomAlgorithm.h"

RandomAlgorithm::RandomAlgorithm() {
	// TODO Auto-generated constructor stub

}

RandomAlgorithm::~RandomAlgorithm() {
	// TODO Auto-generated destructor stub
}

void RandomAlgorithm::run(unsigned int numberOfRuns) {
	if(this->isInitialised){
		this->result->numberOfSteps = numberOfRuns;
		this->result->historicalCosts = new unsigned int [numberOfRuns];
		opInit(this->problemSize);
		unsigned int minCost;
		auto begin = std::chrono::high_resolution_clock::now();
		// First run outside forloop to avoid if inside forloop
		this->rateSolution();
		minCost = this->result->cost;
		this->result->historicalCosts[0] = this->result->cost;
		for(unsigned int i = 1; i < numberOfRuns; i++){
			this->result->lastPermutation = generateRandomPermutation();
			this->rateSolution();
			this->result->historicalCosts[i] = this->result->cost;
			if(this->result->cost < minCost){
				memcpy(this->result->bestPermutation, this->result->lastPermutation, sizeof(unsigned int) * this->problemSize);
				minCost = this->result->cost;
			}
		}
		this->result->cost = minCost;
		auto end = std::chrono::high_resolution_clock::now();
		this->result->workTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1e9;
	}
}
