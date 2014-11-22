/*
 * TabuSearchAlgorithm.h
 *
 *  Created on: 22.11.2014
 */

#ifndef TABUSEARCHALGORITHM_H_
#define TABUSEARCHALGORITHM_H_

#include "BaseAlgorithm.h"
#include <cstdio>
#include <cstring>
#include <iostream>

class TabuSearchAlgorithm: public BaseAlgorithm {
private:
	TabuSearchAlgorithm();
	stopCondition cond;
	int stopVal;
	/**
	 * Number of best neighbours to take into account.
	 */
	unsigned int bestNeighboursNumber;
	/**
	 * Size of tabu.
	 */
	unsigned int tabuSolutionsNumber;
	/**
	 * Indexes of problemSize/10 neighbours with lowest cost.
	 */
	unsigned int * bestNeighboursIndexes;
	/**
	 * Costs of best neighbours.
	 */
	unsigned int * bestNeighboursCosts;
	/**
	 * Last problemSize/4 solution.
	 */
	unsigned int ** tabuSolutions;
	/**
	 * Save indexes of problemSize/10 with lowest costs and store it in bestNeighboursIndexes.
	 */
	void findBestNeighbours();
	/**
	 * Puts new neighbour index at given position and shifts all others down.
	 */
	void insertGoodNeighbour(unsigned int solutionIndex, unsigned int pos);
	/**
	 * Add given solution to list of tabuSolutions.
	 */
	void addTabuSolution(unsigned int solutionIndex);
	/**
	 * Checks if solution is in tabu list.
	 */
	bool isTabu(unsigned int solutionIndex);
public:
	TabuSearchAlgorithm(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed = 19910401);
	virtual ~TabuSearchAlgorithm();
	virtual void init(unsigned int size, int** matA, int** matB, stopCondition condition, int value, int seed = 19910401);
	virtual void clean();
	void run();
	void repeatedRun(unsigned int repetitions);
};

#endif /* TABUSEARCHALGORITHM_H_ */
