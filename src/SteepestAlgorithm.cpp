/*
 * SteepestAlgorithm.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: jacek
 */

#include "../inc/SteepestAlgorithm.h"

SteepestAlgorithm::SteepestAlgorithm(int size, int** matA, int** matB, int seed) : BaseAlgorithm(size, matA, matB, seed) {

}

SteepestAlgorithm::~SteepestAlgorithm() {
    // TODO Auto-generated destructor stub
}

void SteepestAlgorithm::run(stopCondition condition, double value) {
    if(isInitialised) {
        result->historicalCosts = new unsigned int [(unsigned int)value];
//        unsigned int neighbourNumber = problemSize*(problemSize-1)/2;
        //TODO Figure out how to present many runs. Now set to 1

        result->bestPermutation = randomSolution;
        result->lastPermutation = result->bestPermutation; // for in this algorithm they are always the same
        rateSolution();
        result->historicalCosts[0] = result->cost;
        if(condition == DEFINITE_NUM_OF_STEPS) {
            auto begin = std::chrono::high_resolution_clock::now();
            result->numberOfSteps = (int)value;

            for(unsigned int i = 1; i < result->numberOfSteps; i++) {
                generateAllNeighbours();
                int lowestCostNeighIndex = -1;
                for(unsigned int n = 0; n < neighbourhoodSize; n++) {
                    int currentNeighCost = rateNeighbour(n);
                    if(currentNeighCost + result->cost <= result->cost) {
                        lowestCostNeighIndex = (int)n;
                        result->cost += currentNeighCost;
                    }
                }

                if(lowestCostNeighIndex > 0) {
                    memcpy(result->bestPermutation, neighbours[lowestCostNeighIndex], sizeof(unsigned int) * problemSize);
                    result->historicalCosts[i] = result->cost;
                } else {
                    result->numberOfSteps = i;
                    break;
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            result->workTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1e9;
        } else if(condition == MIN_IMPROVEMENT) {
            //TODO Implement minimal improvement stop condition
        } else {
            std::cout << "Unknown stop condition." << std::endl;
        }
        delete[] result->historicalCosts;
    }
}

void SteepestAlgorithm::repeatedRun(unsigned int repetitions, stopCondition condition, double value) {
    double elapsedTime = 0.0;
    unsigned int elapsedSteps = 0;
    int lowestCost = 1e9;
    unsigned int* bestSolution = new unsigned int[problemSize];

    for(unsigned int i = 0; i < repetitions; i++) {
        run(condition, value);
        elapsedTime += result->workTime;
        elapsedSteps += result->numberOfSteps;
        if(lowestCost > result->cost) {
            lowestCost = result->cost;
            memcpy(bestSolution, result->bestPermutation, sizeof(unsigned int) * problemSize);
        }
    }

    memcpy(result->bestPermutation, bestSolution, sizeof(unsigned int) * problemSize);
    result->cost = lowestCost;
    result->workTime = elapsedTime;
    result->numberOfSteps = elapsedSteps;
    delete[] bestSolution;
}
