/*
 * RandomAlgorithm.cpp
 *
 *  Created on: Oct 22, 2014
 */

#include "../inc/RandomAlgorithm.h"

RandomAlgorithm::RandomAlgorithm(unsigned int size, int** matA, int** matB, unsigned int numberOfRuns, int seed)
                    : BaseAlgorithm(size, matA, matB, seed) {
    numberOfSteps = numberOfRuns;
    historicalCosts = new int[numberOfSteps];
}

void RandomAlgorithm::init(unsigned int size, int** matA, int** matB, unsigned int numberOfRuns, int seed) {
    clean();
    BaseAlgorithm::init(size, matA, matB, seed);
    numberOfSteps = numberOfRuns;
    historicalCosts = new int[numberOfSteps];
}

RandomAlgorithm::~RandomAlgorithm() {
    clean();
}

void RandomAlgorithm::clean() {
    if(isInitialised) {
        if(historicalCosts) delete[] historicalCosts;
        BaseAlgorithm::clean();
    }
}

void RandomAlgorithm::run() {
    if(isInitialised) {
        auto begin = std::chrono::high_resolution_clock::now();

        // First run outside for loop to avoid if inside for loop
        minCost = curCost = rateSolution();
        historicalCosts[0] = curCost;
        for(unsigned int i = 1; i < numberOfSteps; i++) {
            generateRandomPermutation();
            memcpy(curSolution, randomSolution, sizeof(unsigned int) * problemSize);
            historicalCosts[i] = rateSolution();
            if(historicalCosts[i] < minCost) {
                memcpy(bestSolution, curSolution, sizeof(unsigned int) * problemSize);
                minCost = historicalCosts[i];
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        workTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1.e9;
        curCost = historicalCosts[numberOfSteps-1];
    }
}
