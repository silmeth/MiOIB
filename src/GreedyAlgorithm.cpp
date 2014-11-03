/*
 * GreedyAlgorithm.cpp
 *
 *  Created on: 29.10.2014
 *      Author: jacek
 */

#include "../inc/GreedyAlgorithm.h"

GreedyAlgorithm::GreedyAlgorithm(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed)
                        : BaseAlgorithm(size, matA, matB, seed), cond(condition), stopVal(value) {
        historicalCosts = new int[value];
}

void GreedyAlgorithm::init(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed) {
    clean();
    BaseAlgorithm::init(size, matA, matB, seed);
    historicalCosts = new int[value];
    cond = condition;
    stopVal = value;
}

GreedyAlgorithm::~GreedyAlgorithm() {
    clean();
}

void GreedyAlgorithm::clean() {
      if(isInitialised) {
            if(historicalCosts) delete[] historicalCosts;
            BaseAlgorithm::clean();
        }
}

void GreedyAlgorithm::run() {
    if(isInitialised) {
        minCost = curCost = rateSolution();
        historicalCosts[0] = curCost;
        unsigned int sameVal = 0;
        if(cond == DEFINITE_NUM_OF_STEPS) {
            numberOfSteps = stopVal;
            auto begin = std::chrono::high_resolution_clock::now();
            std::uniform_int_distribution<unsigned int> dist(0, neighbourhoodSize-1);

            bool betterSolutionFound = true;
            int currentNeighCost;
            for(unsigned int i = 1; i < stopVal; i++) {
                unsigned int r = dist(randGen); // random for randomly chosen first neighbour
                if(betterSolutionFound) {
                    betterSolutionFound = false;
                    for(unsigned int k = 0; k < neighbourhoodSize; k++) {
                        unsigned int n = (r+k)%neighbourhoodSize;
                        generateNeighbour(n);
                        currentNeighCost = curCost + rateNeighbour(n);
                        if(currentNeighCost < curCost) {
                            curCost = currentNeighCost;
                            memcpy(curSolution, neighbours[n], sizeof(unsigned int) * problemSize);
                            historicalCosts[i] = curCost;
                            betterSolutionFound = true;
                            sameVal = 0;
                            break;
                        } else if(currentNeighCost == curCost && sameVal < 3) {
                            curCost = currentNeighCost;
                            memcpy(curSolution, neighbours[n], sizeof(unsigned int) * problemSize);
                            historicalCosts[i] = curCost;
                            betterSolutionFound = true;
                            ++sameVal;
                            break;
                        }
                    }
                } else {
                    // i-1 because if program executes this block, it means it has unset betterSolutionFound
                    // in (i-1)-th step and then i has been incremented.
                    numberOfSteps = i-1;
                    break;
                }
                if(i == stopVal-1) {
                    std::cerr << "Greedy: Maximum number of steps (" << numberOfSteps << ") has been reached!\n";
                }
            }
//            std::cout << "Greedy no of steps: " << numberOfSteps << std::endl;
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

void GreedyAlgorithm::repeatedRun(unsigned int repetitions) {
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
