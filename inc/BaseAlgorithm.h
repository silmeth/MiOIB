/*
 * BaseAlgorithm.h
 *
 *  Created on: Oct 22, 2014
 */

#ifndef BASEALGORITHM_H_
#define BASEALGORITHM_H_

#include <cstddef>
#include <cassert>
#include <cstring>
#include <iostream>
#include <random>
#include <chrono>

// #include "operations.h"

enum stopCondition {
    DEFINITE_NUM_OF_STEPS = 0,
    MIN_IMPROVEMENT = 1
};

void switchElements(int* permutation, unsigned int pos1, unsigned int pos2);

typedef struct {
    unsigned int problemSize;
    // Cost of the best permutation = solution.
    int cost;
    // Pointer to the best permutation.
    unsigned int* bestPermutation;
    // Pointer to last permutation
    unsigned int* lastPermutation;
    /**
     * Number of steps needed to find solution.
     * If program is run with DEFINITE_NUM_OF_STEPS, step in which the best solution was found is stored here.
     */
    unsigned int numberOfSteps;
    /**
     * Stores costs of permutation from each step.
     * Needed for plotting improvement of solution over time.
     */
    unsigned int* historicalCosts;
    // Time needed to get solution
    double workTime;
} runResult;

class BaseAlgorithm {
private:
    BaseAlgorithm();

public:
    /**
     * Initialises the algorithm.
     * Allocates memory and creates a random permutation (start permutation).
     */
    BaseAlgorithm(int size, int** matA, int** matB, int seed = 19910401);
    virtual ~BaseAlgorithm();

    /**
     * Runs the algorithm.
     * @param numberOfRuns Number of runs of the algorithm.
     * @param stopCondition Type of stop condition.
     * @param value Depending on stop condition either number of steps or minimal improvement.
     * @return runResult After reaching stop condition it returns a structure containing all parameters required for further processing.
     */
    void run(int numberOfRuns, stopCondition condition, double value);
    /**
     * Removes unnecessary data structures.
     */
    void clean();
    /**
     * Calculates cost for given permutation in O(n^2) time and stores it in result->cost.
     @param solution Optional pointer to solution to be rated; if not given, result->lastPermutation is used.
     */
    int rateSolution(unsigned int* solution = NULL);

    /**
     * Calculates cost change from current solution to its neighbour in O(n) time.
     * @param id Index of neighbour to be rated, must be in range [0; neighbourhoodSize).
     * @return Calculated cost change.
     */
    int rateNeighbour(unsigned int id);

    void generateAllNeighbours();

    void generateRandomPermutation();

    /*
     * Random permutation initialised in init().
     */
    unsigned int problemSize;
    unsigned int neighbourhoodSize;
    unsigned int** neighbours;
    unsigned int** neighbourSwaps;
//    unsigned int* curSolution;
    unsigned int* randomSolution;
    std::mt19937 randGen;

    runResult* result;
    int** A;
    int** B;
    bool isInitialised;
};

#endif /* BASEALGORITHM_H_ */
