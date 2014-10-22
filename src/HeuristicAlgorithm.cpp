/*
 * HeuristicAlgorithm.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: jacek
 */

#include "../inc/HeuristicAlgorithm.h"

HeuristicAlgorithm::HeuristicAlgorithm() {
	// TODO Auto-generated constructor stub

}

HeuristicAlgorithm::~HeuristicAlgorithm() {
	// TODO Auto-generated destructor stub
}

void HeuristicAlgorithm::run(){
	if(this->isInitialised){
		this->result->lastPermutation = new unsigned int [this->problemSize];
		unsigned int* solution = this->result->lastPermutation;

		// Begin measuring time
		auto begin = std::chrono::high_resolution_clock::now();
		bool* isAUsed = new bool[this->problemSize];
	    bool* isBUsed = new bool[this->problemSize];
	    for(unsigned int i = 0; i < this->problemSize; i++) {
	        isAUsed[i] = false;
	        isBUsed[i] = false;
	    }

	    for(unsigned int k = 0; k < this->problemSize; k++) {
	        bool first = true;
	        int iAMax = 0;
	        int jAMax = 0;
	        int AMax = 0;
	        int iBMin = 0;
	        int jBMin = 0;
	        int BMin = 0;
	        for(unsigned int i = 0; i < this->problemSize; i++) {
	            for(unsigned int j = 0; j < this->problemSize; j++) {
	                if(i != j) {
	                    if(first) {
	                        AMax = this->A[i][j];
	                        iAMax = i;
	                        jAMax = j;
	                        BMin = this->B[i][j];
	                        iBMin = i;
	                        jBMin = j;
	                        first = false;
	                    } else {
	                        if(this->A[i][j] > AMax && !isAUsed[i] && !isAUsed[j]) {
	                            iAMax = i;
	                            jAMax = j;
	                        }
	                        if(this->B[i][j] < BMin && !isBUsed[i] && !isBUsed[j]) {
	                            iBMin = i;
	                            jBMin = j;
	                        }
	                    }
	                }
	            }
	        }
	        solution[iAMax] = iBMin;
	        solution[jAMax] = jBMin;

	        isAUsed[iAMax] = true;
	        isAUsed[jAMax] = true;
	        isBUsed[iBMin] = true;
	        isBUsed[jBMin] = true;
	    }
	    auto end = std::chrono::high_resolution_clock::now();
	    this->result->workTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1e9;
	    delete[] isAUsed;
	    delete[] isBUsed;
	    this->rateSolution();
	    this->result->numberOfSteps = 1;
	    this->result->historicalCosts = NULL;
	}
}