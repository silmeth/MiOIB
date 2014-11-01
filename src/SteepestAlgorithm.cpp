/*
 * SteepestAlgorithm.cpp
 *
 *  Created on: Oct 22, 2014
 */

#include "../inc/SteepestAlgorithm.h"

SteepestAlgorithm::SteepestAlgorithm(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed)
                    : BaseAlgorithm(size, matA, matB, seed), cond(condition), stopVal(value) {
    historicalCosts = new int[value];
}

void SteepestAlgorithm::init(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed) {
    clean();
    BaseAlgorithm::init(size, matA, matB, seed);
    historicalCosts = new int[value];
    cond = condition;
    stopVal = value;
}

SteepestAlgorithm::~SteepestAlgorithm() {
    clean();
}

void SteepestAlgorithm::clean() {
    if(isInitialised) {
        if(historicalCosts) delete[] historicalCosts;
        BaseAlgorithm::clean();
    }
}

void SteepestAlgorithm::run() {
    if(isInitialised) {
        minCost = curCost = rateSolution();
        historicalCosts[0] = curCost;
        numberOfSteps = stopVal; // If steepest doesn't stop before reaching stopVal
        if(cond == DEFINITE_NUM_OF_STEPS) {
            auto begin = std::chrono::high_resolution_clock::now();

            for(unsigned int i = 1; i < stopVal; i++) {
                generateAllNeighbours();
                int lowestCostNeighIndex = -1;
                int minNeighCost = curCost;

                for(unsigned int n = 0; n < neighbourhoodSize; n++) {
                    int currentNeighCost = curCost + rateNeighbour(n);
                    if(currentNeighCost <= minNeighCost) {
                        lowestCostNeighIndex = (int)n;
                        minNeighCost = currentNeighCost;
                    }
                }
                if(lowestCostNeighIndex > 0) {
                    curCost = minNeighCost;
                    memcpy(curSolution, neighbours[lowestCostNeighIndex], sizeof(unsigned int) * problemSize);
                    historicalCosts[i] = curCost;
                } else {
                    numberOfSteps = i;
                    break;
                }
            }
            auto end = std::chrono::high_resolution_clock::now();
            workTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1.e9;
            minCost = curCost;
            memcpy(bestSolution, curSolution, sizeof(unsigned int) * problemSize);
        } else if(cond == MIN_IMPROVEMENT) {
            //TODO Implement minimal improvement stop condition
        } else {
            std::cout << "Unknown stop condition." << std::endl;
        }
    }
}

void SteepestAlgorithm::repeatedRun(unsigned int repetitions) {
    double elapsedTime = 0.0;
    unsigned int elapsedSteps = 0;
    int lowestCost = 1e9;
    unsigned int* bestSolTmp = new unsigned int[problemSize];

    for(unsigned int i = 0; i < repetitions; i++) {
        // initialise randomly
        generateRandomPermutation();
        memcpy(curSolution, randomSolution, sizeof(unsigned int) * problemSize);
        run();
        elapsedTime += workTime;
        elapsedSteps += numberOfSteps;
        if(lowestCost > curCost) {
            lowestCost = minCost;
            memcpy(bestSolTmp, bestSolution, sizeof(unsigned int) * problemSize);
        }
    }

    memcpy(bestSolution, bestSolTmp, sizeof(unsigned int) * problemSize);
    minCost = lowestCost;
    workTime = elapsedTime;
    numberOfSteps = elapsedSteps;
    delete[] bestSolTmp;
}
