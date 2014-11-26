/*
 * TabuSearchAlgorithm.cpp
 *
 *  Created on: 22.11.2014
 */

#include "../inc/TabuSearchAlgorithm.h"


TabuSearchAlgorithm::TabuSearchAlgorithm(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed)
                    : BaseAlgorithm(size, matA, matB, seed), cond(condition), stopVal(value) {
    historicalCosts = new int[value];
    // For small problems always take 3 neighbours.
     if(problemSize < 30) {
     	bestNeighboursNumber = 3;
     }
     else {
     	bestNeighboursNumber = problemSize/10;
     }
     bestNeighboursIndexes = new unsigned int[bestNeighboursNumber];
     bestNeighboursCosts = new unsigned int[bestNeighboursNumber];
     tabuSolutionsNumber = problemSize/4;
     tabuSolutions = new unsigned int * [tabuSolutionsNumber];
     for(unsigned int i = 0; i < tabuSolutionsNumber; ++i) {
     	tabuSolutions[i] = new unsigned int[problemSize];
     }
}

void TabuSearchAlgorithm::init(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed) {
    clean();
    BaseAlgorithm::init(size, matA, matB, seed);
    historicalCosts = new int[value];
    cond = condition;
    stopVal = value;
}

TabuSearchAlgorithm::~TabuSearchAlgorithm() {
    clean();
}

void TabuSearchAlgorithm::clean() {
    if(isInitialised) {
        if(historicalCosts) delete[] historicalCosts;
        BaseAlgorithm::clean();
    }
    delete [] bestNeighboursIndexes;
    delete [] bestNeighboursCosts;
    for(unsigned int i = 0; i < tabuSolutionsNumber; ++i) {
    	delete [] tabuSolutions[i];
    }
    delete [] tabuSolutions;
}

void TabuSearchAlgorithm::run() {
    if(isInitialised) {
        minCost = curCost = rateSolution();
        historicalCosts[0] = curCost;
        numberOfSteps = stopVal; // If steepest doesn't stop before reaching stopVal
        unsigned int sameOrWorseCounter = 0;
		auto begin = std::chrono::high_resolution_clock::now();

		for(unsigned int i = 1; i < stopVal; i++) {
			generateAllNeighbours();
			findBestNeighbours();
			bool nextSolutionFound = false;
			// Iterate over bestNeighboursNumber
			for(unsigned int n = 0; n < bestNeighboursNumber; n++) {
				if(!nextSolutionFound) {
					//If it's the last one, accept it.
					if(n == bestNeighboursNumber - 1) {
						nextSolutionFound = true;
						if(bestNeighboursCosts[n] >= minCost)
                            sameOrWorseCounter++;
                        else
                            sameOrWorseCounter = 0;
					} else {
						// Check if it has lower cost than current solution.
						if(bestNeighboursCosts[n] < curCost) {
                            if(bestNeighboursCosts[n] < minCost) {
                                nextSolutionFound = true;
                                sameOrWorseCounter = 0;
                                minCost = bestNeighboursCosts[n];
                                memcpy(bestSolution, neighbours[bestNeighboursIndexes[n]], sizeof(unsigned int) * problemSize);
                            } else if(!isTabu(bestNeighboursIndexes[n])) {
                                nextSolutionFound = true;
                                sameOrWorseCounter++;
                            }
						} else if(!isTabu(bestNeighboursIndexes[n])) {
							nextSolutionFound = true;
							sameOrWorseCounter++;
						}
					}
				}
				if(nextSolutionFound) {
					addTabuSolution(bestNeighboursIndexes[n]);
					curCost = bestNeighboursCosts[n];
					memcpy(curSolution, neighbours[bestNeighboursIndexes[n]], sizeof(unsigned int) * problemSize);
					historicalCosts[i] = curCost;
					if(i == stopVal-1) {
                        // numberOfSteps+1 because it is updated later, so current value should be 1 bigger than it's
                        // in the memory
                        std::cerr << "Tabu Search: Maximum number of steps (" << numberOfSteps+1 << ") has been reached!\n";
                    }
					break;
				}
			}
			if(sameOrWorseCounter > 10*neighbourhoodSize) {
				numberOfSteps = i+1;
				break;
			}
		}
//        std::cout << "Tabu no of steps: " << numberOfSteps << std::endl;
		auto end = std::chrono::high_resolution_clock::now();
		workTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1.e9;
    }
}

void TabuSearchAlgorithm::repeatedRun(unsigned int repetitions) {
//    double elapsedTime = 0.0;
//    unsigned int elapsedSteps = 0;
//    int lowestCost = 1e9;
//    unsigned int* bestSolTmp = new unsigned int[problemSize];
//
//    for(unsigned int i = 0; i < repetitions; i++) {
//        // initialise randomly
//        generateRandomPermutation();
//        memcpy(curSolution, randomSolution, sizeof(unsigned int) * problemSize);
//        run();
//        elapsedTime += workTime;
//        elapsedSteps += numberOfSteps;
//        if(lowestCost > curCost) {
//            lowestCost = minCost;
//            memcpy(bestSolTmp, bestSolution, sizeof(unsigned int) * problemSize);
//        }
//    }
//
//    memcpy(bestSolution, bestSolTmp, sizeof(unsigned int) * problemSize);
//    minCost = lowestCost;
//    workTime = elapsedTime;
//    numberOfSteps = elapsedSteps;
//    delete[] bestSolTmp;
}

void TabuSearchAlgorithm::findBestNeighbours() {
	for(unsigned int i = 0; i < bestNeighboursNumber; ++i) {
		bestNeighboursCosts[i] = 1e10;
	}
	for(unsigned int n = 0; n < neighbourhoodSize; ++n) {
		for(unsigned int i = 0; i < bestNeighboursNumber; ++i) {
			if(rateNeighbour(n) + curCost < bestNeighboursCosts[i]){
				insertGoodNeighbour(n, i);
			}
		}
	}
}

void TabuSearchAlgorithm::insertGoodNeighbour(unsigned int solutionIndex, unsigned int pos) {
	// Shift one step down.
	for(unsigned int i = pos + 1; i < bestNeighboursNumber-1; ++i) {
		bestNeighboursCosts[i+1] = bestNeighboursCosts[i];
		bestNeighboursIndexes[i+1] = bestNeighboursIndexes[i];
	}
	bestNeighboursCosts[pos] = rateNeighbour(solutionIndex) + curCost;
	bestNeighboursIndexes[pos] = solutionIndex;
}

void TabuSearchAlgorithm::addTabuSolution(unsigned int solutionIndex) {
	for(unsigned int i = 0; i < tabuSolutionsNumber - 1; ++i) {
		memcpy(tabuSolutions[i+1], tabuSolutions[i], sizeof(unsigned int) * problemSize);
	}
	memcpy(tabuSolutions[0], neighbours[solutionIndex], sizeof(unsigned int) * problemSize);
}

bool TabuSearchAlgorithm::isTabu(unsigned int solutionIndex) {
	bool inTabu = false;
	for(unsigned int n = 0; n < tabuSolutionsNumber; ++n) {
		unsigned int identicalElementCounter = 0;
		for(unsigned int i = 0; i < problemSize; ++i) {
			if(neighbours[solutionIndex][i] == tabuSolutions[n][i])
				identicalElementCounter++;
		}
		if(identicalElementCounter == problemSize) {
			inTabu = true;
		}
	}
	return inTabu;
}

