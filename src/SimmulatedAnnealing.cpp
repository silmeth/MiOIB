/*
 * SimmulatedAnnealing.cpp
 *
 *  Created on: 22.11.2014
 */

#include "../inc/SimmulatedAnnealing.h"

SimmulatedAnnealing::SimmulatedAnnealing(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed)
                    : BaseAlgorithm(size, matA, matB, seed), cond(condition), stopVal(value) {
    historicalCosts = new int[value];
    lowestTemperature = 0.01;
}

SimmulatedAnnealing::~SimmulatedAnnealing() {
	clean();
}

void SimmulatedAnnealing::init(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed) {
    clean();
    BaseAlgorithm::init(size, matA, matB, seed);
    historicalCosts = new int[value];
    cond = condition;
    stopVal = value;
}

void SimmulatedAnnealing::clean() {
    if(isInitialised) {
        if(historicalCosts) delete[] historicalCosts;
        BaseAlgorithm::clean();
    }
}

void SimmulatedAnnealing::run() {
    if(isInitialised) {
        minCost = curCost = rateSolution();
        historicalCosts[0] = curCost;
        // Number of checked solutions
        unsigned int checkedSolutions = 0;
        unsigned int currentNeighCost;
        // Iterator
        unsigned int i = 1;
        initTemp(getWorstNeighbourCost());
        // How many solutions checked since last improvement.
        unsigned int lastImprovement = 0;
		unsigned int k = 0;

        auto begin = std::chrono::high_resolution_clock::now();
        std::uniform_int_distribution<unsigned int> dist(0, neighbourhoodSize-1);
        // Generator for comparing with threshold.
        std::uniform_real_distribution<double> solAcc(0.0, 1.0);

        // Only one stop condition, but in code i can be set to stopVal to terminate loop.
        while(i < stopVal) {
            if(i % (neighbourhoodSize) == 0) {
            	decreaseTemperature(0.8);
            }
            unsigned int r = dist(randGen);
			bool accepted = false;

			while(!accepted) {
				if(lastImprovement > 10*neighbourhoodSize) {
					i = stopVal;
					std::cerr << "Reached 10 * " << neighbourhoodSize << std::endl;
					break;
				}
				unsigned int n = (r+k)%neighbourhoodSize; // Iterate over all neighbours unlimited number of times.
				generateNeighbour(n);
				checkedSolutions++;
				currentNeighCost = curCost + rateNeighbour(n);
				// Check if take this solution
				float threshold = acceptSolutionThreshold(currentNeighCost);

				// Compare with threshold
				if(solAcc(randGen) < threshold) {
					// Add solution
					accepted = true;
					curCost = currentNeighCost;
					memcpy(curSolution, neighbours[n], sizeof(unsigned int) * problemSize);
					historicalCosts[i] = curCost;
					if(curCost < minCost) {
						lastImprovement = 0;
						minCost = curCost;
						memcpy(bestSolution, neighbours[n], sizeof(unsigned int) * problemSize);
					} else {
						lastImprovement++;
					}
					break;
				} else {
					lastImprovement++;
				}
				k++;
			}
			i++;
			numberOfSteps = i;
			if(i == stopVal-1) {
				std::cerr << "SimulatedAnnealing: Maximum number of steps (" << numberOfSteps << ") has been reached!\n";
			}
        }
		auto end = std::chrono::high_resolution_clock::now();
		workTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1.e9;
    }
}

void SimmulatedAnnealing::repeatedRun(unsigned int repetitions) {
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

float SimmulatedAnnealing::initTemp(unsigned int worstNeighbourCost) {
	temperature = float((curCost - worstNeighbourCost)) / log(0.95);
	return temperature;
}

float SimmulatedAnnealing::decreaseTemperature(float multiplier) {
	temperature *= multiplier;
	return temperature;
}

float SimmulatedAnnealing::acceptSolutionThreshold(unsigned int cost) {
	return exp(float(minCost - cost)/temperature);
}

unsigned int SimmulatedAnnealing::getWorstNeighbourCost() {
	double highestCost = -1e9;
	unsigned int worstNeighbourIndex = 0;
	for(unsigned int n = 0; n < neighbourhoodSize; ++n) {
		if(rateNeighbour(n) > highestCost) {
			highestCost = rateNeighbour(n);
			worstNeighbourIndex = n;
		}
	}
	return highestCost + curCost;
}
