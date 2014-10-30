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

void Lab1::task2() {
	int repetitions = 200;
	int numberOfInstances;
	char input[50];
	std::vector<std::string> problemNames;
	problemNames.push_back("chr12a");
	problemNames.push_back("chr15a");
	problemNames.push_back("chr18a");
	numberOfInstances = problemNames.size();

	ProblemInstance** instances;
	instances = new ProblemInstance* [numberOfInstances];
	for(int i = 0; i < numberOfInstances; i++) {
		sprintf(input, "./qapdatsol/%s.dat", problemNames.at(i).c_str());
		instances[i] = new ProblemInstance(input);
	}

	for(int i = 0; i < numberOfInstances; i++) {
		RandomAlgorithm randAlg(instances[i]->problemSize, instances[i]->A, instances[i]->B, 200);
		SteepestAlgorithm steepAlg(instances[i]->problemSize, instances[i]->A, instances[i]->B, DEFINITE_NUM_OF_STEPS, 30);
		std::vector<double> randAlgCosts;
		std::vector<double> steepAlgCosts;
		for(int j = 0; j < repetitions; j++) {
			randAlg.run();
			randAlgCosts.push_back((double)randAlg.minCost);
		}
		steepAlg.repeatedRun(repetitions);
		// !!! Historical costs aren't stored for repeated run. If needed, might be added, later. !!!
//		for(int j = 0; j < repetitions; j++) {
//			steepAlgCosts.push_back((double)steepAlg.historicalCosts[j]);
//		}
	}
	//unsigned int size, int** matA, int** matB, unsigned int numberOfRuns, int seed=19910401
	for(int i = 0; i < numberOfInstances; i++) {
		delete instances[i];
	}
	delete [] instances;
}
