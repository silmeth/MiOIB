/*
 * Lab1.cpp
 *
 *  Created on: 29.10.2014
 *      Author: jacek
 */

#include "../inc/Lab1.h"

Lab1::Lab1() {
	// TODO Auto-generated constructor stub
}

Lab1::~Lab1() {

}

void Lab1::task() {
	problemNames.push_back("tai35b");
	problemNames.push_back("chr15a");
	problemNames.push_back("chr18a");
	numberOfInstances = problemNames.size();

	ProblemInstance** instances;
	instances = new ProblemInstance* [numberOfInstances];
	for(int i = 0; i < numberOfInstances; i++) {
		sprintf(input, "./qapdatsol/%s.dat", problemNames.at(i).c_str());
		instances[i] = new ProblemInstance(input);
	}

	// Costs of best solutions found by each algorithm for each instance
	double** bestSolutions;
	// Std dev of costs of solutions found by each algorithm for each instance
	double** solutionStdDev;
	// Means of costs of solutions found by each algorithm for each instance
	double** solutionMeans;
	// Std dev of worktime spent by each algorithm on each instance
	double** workTimeStdDev;
	// Means of worktime spent by each algorithm on each instance
	double** workTimeMeans;
	// Number of steps done for each instance (will depend on the number of repetitions)
	unsigned int** numberOfSteps;
	bestSolutions = new double* [numberOfInstances];
	solutionStdDev = new double* [numberOfInstances];
	solutionMeans = new double* [numberOfInstances];
	workTimeStdDev = new double* [numberOfInstances];
	workTimeMeans = new double* [numberOfInstances];
	numberOfSteps = new unsigned int* [numberOfInstances];
	for(int i = 0; i < numberOfInstances; ++i) {
		// 3 is sum of Steepes, Greedy and Random
		bestSolutions[i] = new double [4];
		solutionStdDev[i] = new double [3];
		solutionMeans[i] = new double [3];
		workTimeStdDev[i] = new double [3];
		workTimeMeans[i] = new double [3];
		numberOfSteps[i] = new unsigned int [2];
	}

	for(int i = 0; i < numberOfInstances; ++i) {
		RandomAlgorithm randAlg(instances[i]->problemSize, instances[i]->A, instances[i]->B, 30);
		SteepestAlgorithm steepAlg(instances[i]->problemSize, instances[i]->A, instances[i]->B, DEFINITE_NUM_OF_STEPS, 30);
		GreedyAlgorithm greedyAlg(instances[i]->problemSize, instances[i]->A, instances[i]->B, DEFINITE_NUM_OF_STEPS, 30);
		HeuristicAlgorithm heurAlg(instances[i]->problemSize, instances[i]->A, instances[i]->B);
		std::vector<double> randAlgCosts;
		std::vector<double> steepAlgCosts;
		std::vector<double> steepAlgInitCosts;
		std::vector<double> steepAlgNumberOfSteps;
		std::vector<double> steepAlgWorkTime;
		std::vector<double> greedyAlgCosts;
		std::vector<double> greedyAlgInitCosts;
		std::vector<double> greedyAlgNumberOfSteps;
		std::vector<double> greedyAlgWorkTime;

		heurAlg.run();

		randAlg.run();
		for(unsigned int j = 0; j < randAlg.numberOfSteps; ++j) {
			randAlgCosts.push_back((double)randAlg.historicalCosts[j] / (double)instances[i]->lowestCost);
		}

		for(int j = 0; j < repetitions; ++j) {
			// Ugly use of memcpy(), we should change run() method of each algorithm
			steepAlg.generateRandomPermutation();
			memcpy(steepAlg.curSolution, steepAlg.randomSolution, sizeof(unsigned int) * steepAlg.problemSize);
			steepAlgInitCosts.push_back(steepAlg.rateSolution());
			steepAlg.run();
			steepAlgCosts.push_back(steepAlg.curCost / (double)instances[i]->lowestCost);
			steepAlgWorkTime.push_back(steepAlg.workTime);
			steepAlgNumberOfSteps.push_back(steepAlg.numberOfSteps);

			greedyAlg.generateRandomPermutation();
			memcpy(greedyAlg.curSolution, greedyAlg.randomSolution, sizeof(unsigned int) * greedyAlg.problemSize);
			greedyAlgInitCosts.push_back(steepAlg.rateSolution());
			greedyAlg.run();
			greedyAlgCosts.push_back(greedyAlg.minCost / (double)instances[i]->lowestCost);
			greedyAlgWorkTime.push_back(greedyAlg.workTime);
			greedyAlgNumberOfSteps.push_back(greedyAlg.numberOfSteps);
		}

		bestSolutions[i][GREEDY] = *std::min_element(greedyAlgCosts.begin(), greedyAlgCosts.end());
		bestSolutions[i][STEEPEST] = *std::min_element(steepAlgCosts.begin(), steepAlgCosts.end());
		bestSolutions[i][RANDOM] = *std::min_element(randAlgCosts.begin(), randAlgCosts.end());
		bestSolutions[i][HEURISTIC] = heurAlg.minCost / (double)instances[i]->lowestCost;
		solutionStdDev[i][GREEDY] = stdDev(greedyAlgCosts);
		solutionStdDev[i][STEEPEST] = stdDev(steepAlgCosts);
		solutionStdDev[i][RANDOM] = stdDev(randAlgCosts);
		solutionMeans[i][GREEDY] = mean(greedyAlgCosts);
		solutionMeans[i][STEEPEST] = mean(steepAlgCosts);
		solutionMeans[i][RANDOM] = mean(randAlgCosts);
		workTimeStdDev[i][GREEDY] = stdDev(greedyAlgWorkTime);
		workTimeStdDev[i][STEEPEST] = stdDev(steepAlgWorkTime);
		workTimeStdDev[i][RANDOM] = 0.0;
		workTimeMeans[i][GREEDY] = mean(greedyAlgWorkTime);
		workTimeMeans[i][STEEPEST] = mean(steepAlgWorkTime);
		workTimeMeans[i][RANDOM] = randAlg.workTime / (double)repetitions;
		numberOfSteps[i][GREEDY] = mean(greedyAlgNumberOfSteps) * repetitions; // Because I'm to lazy to sum it in loop
		numberOfSteps[i][STEEPEST] = mean(steepAlgNumberOfSteps) * repetitions;
	}
	//unsigned int size, int** matA, int** matB, unsigned int numberOfRuns, int seed=19910401
	for(int i = 0; i < numberOfInstances; i++) {
		delete [] instances[i];
		delete [] bestSolutions[i];
		delete [] solutionStdDev[i];
		delete [] solutionMeans [i];
	}
	delete [] bestSolutions;
	delete [] solutionStdDev;
	delete [] solutionMeans;
	delete [] instances;
}

double Lab1::mean(std::vector<double> vec) {
	double sum = 0.0;
	for(std::vector<double>::iterator it = vec.begin(); it != vec.end(); ++it) {
		sum += *it;
	}
	return sum / (double)vec.size();
}

double Lab1::stdDev(std::vector<double> vec) {
	double sum = 0.0;
	double mn = mean(vec);
	for(std::vector<double>::iterator it = vec.begin(); it != vec.end(); ++it) {
		sum += pow(*it - mn, 2.0);
	}
	return sqrt(sum / (double)(vec.size()-1));
}
