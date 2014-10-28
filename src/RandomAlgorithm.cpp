/*
 * RandomAlgorithm.cpp
 *
 *  Created on: Oct 22, 2014
 */

#include "../inc/RandomAlgorithm.h"

RandomAlgorithm::RandomAlgorithm(int size, int** matA, int** matB, int seed) : BaseAlgorithm(size, matA, matB, seed) {

}

RandomAlgorithm::~RandomAlgorithm() {
    // TODO Auto-generated destructor stub
}

void RandomAlgorithm::run(unsigned int numberOfRuns) {
    if(isInitialised) {
        result->numberOfSteps = numberOfRuns;
        result->historicalCosts = new unsigned int[numberOfRuns];

        int minCost;
        auto begin = std::chrono::high_resolution_clock::now();

        // First run outside for loop to avoid if inside for loop
        rateSolution();
        minCost = result->cost;
        result->historicalCosts[0] = result->cost;
        for(unsigned int i = 1; i < numberOfRuns; i++) {
            generateRandomPermutation();
            result->lastPermutation = randomSolution;
            rateSolution();
            result->historicalCosts[i] = result->cost;
            if(result->cost < minCost) {
                memcpy(result->bestPermutation, result->lastPermutation, sizeof(unsigned int) * problemSize);
                minCost = result->cost;
            }
        }
        result->cost = minCost;
        auto end = std::chrono::high_resolution_clock::now();
        result->workTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1e9;
        delete[] result->historicalCosts;
    }
}
