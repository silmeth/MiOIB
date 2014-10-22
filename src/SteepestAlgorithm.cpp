/*
 * SteepestAlgorithm.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: jacek
 */

#include "../inc/SteepestAlgorithm.h"

SteepestAlgorithm::SteepestAlgorithm() {
	// TODO Auto-generated constructor stub

}

SteepestAlgorithm::~SteepestAlgorithm() {
	// TODO Auto-generated destructor stub
}

unsigned int SteepestAlgorithm::rateSolution2(int** A, int** B, unsigned int* solution, unsigned int sz) {
    unsigned int res = 0;
    for(unsigned int i = 0; i < sz; i++) {
        for(unsigned int j = 0; j < sz; j++) {
            res += A[i][j]*B[solution[i]][solution[j]];
        }
    }
    return res;
}

void SteepestAlgorithm::run(stopCondition condition, double value){
	if(this->isInitialised){
		opInit(this->problemSize);
		this->result->historicalCosts = new unsigned int [(unsigned int)value];
		unsigned int neighbourNumber = this->problemSize*(this->problemSize-1)/2;
		//TODO Figure out how to present many runs. Now set to 1
		this->result->bestPermutation = generateRandomPermutation();
		this->rateSolution();
		this->result->historicalCosts[0] = this->result->cost;
		if(condition == definiteNumberOfSteps) {
			auto begin = std::chrono::high_resolution_clock::now();
			this->result->numberOfSteps = (int)value;
			unsigned int** neighbours;
			for(unsigned int i = 1; i < this->result->numberOfSteps; i++) {
				neighbours = generateAllNeighbours(this->result->bestPermutation);
				int lowestCostNeighIndex = -1;
				for(int n = 0; n < neighbourNumber; n++){
					unsigned int currentNeighCost = rateSolution2(this->A, this->B, neighbours[n], this->problemSize);
					if(currentNeighCost <= this->result->cost){
						lowestCostNeighIndex = n;
						this->result->cost = currentNeighCost;
					}
				}
				if(lowestCostNeighIndex > 0) {
					memcpy(this->result->bestPermutation, neighbours[lowestCostNeighIndex], sizeof(unsigned int) * this->problemSize);
					this->result->historicalCosts[i] = this->result->cost;
				}
				else {
					this->result->numberOfSteps = i;
					break;
				}
			}
			auto end = std::chrono::high_resolution_clock::now();
			this->result->workTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1e9;
		}
		else if(condition == minimalImprovement) {
			//TODO Implement minimal improvement stop condition
		}
		else {
			std::cout << "Unknown stop condition." << std::endl;
		}
		opClear();
	}
}

void SteepestAlgorithm::repeatedRun(unsigned int repetitions, stopCondition condition, double value){
	double elapsedTime = 0.0;
	unsigned int elapsedSteps = 0;
	unsigned int lowestCost = 1e9;
	unsigned int* bestSolution = new unsigned int [this->problemSize];
	for(unsigned int i = 0; i < repetitions; i++){
		this->run(condition, value);
		elapsedTime += this->result->workTime;
		elapsedSteps += this->result->numberOfSteps;
		if(lowestCost > this->result->cost){
			lowestCost = this->result->cost;
			memcpy(bestSolution, this->result->bestPermutation, sizeof(unsigned int) * this->problemSize);
		}
	}
	memcpy(this->result->bestPermutation, bestSolution, sizeof(unsigned int) * this->problemSize);
	this->result->cost = lowestCost;
	this->result->workTime = elapsedTime;
	this->result->numberOfSteps = elapsedSteps;
	delete [] bestSolution;
}



