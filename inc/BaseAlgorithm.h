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

enum stopCondition {
    DEFINITE_NUM_OF_STEPS = 0,
    MIN_IMPROVEMENT = 1
};

/**
 * Swaps elements in a given solution vector.
 * @param solution Pointer to the solution to be changed.
 * @param pos1 Position of the first element to be swapped.
 * @param pos2 Position of the second element to be swapped.
 */
void switchElements(unsigned int* solution, unsigned int pos1, unsigned int pos2);

/**
 * Base class for QAP-solving algorithms. All algorithms inherit from this one.
 */
class BaseAlgorithm {
private:
    BaseAlgorithm();
    void initHelp();

public:
    /**
     * Initialises the algorithm.
     * Allocates memory and creates a random permutation (start permutation).
     * @param size Size of the problem to be solved.
     * @param matA The A matrix of the problem definition.
     * @param matB The B matrix of the problem definition.
     * @param seed Seed for random number generator, defaults to 19910401.
     */
    BaseAlgorithm(unsigned int size, int** matA, int** matB, int seed = 19910401);

    virtual ~BaseAlgorithm(); /**< Frees all dynamically allocated memory.*/

    /**
     * Similar to the constructor. Here to let a single algorithm object
     * to be used on multiple different problems many times. It calls destructor first.
     */
    virtual void init(unsigned int size, int** matA, int** matB, int seed = 19910401);

//    /**
//     * Runs the algorithm.
//     * @param numberOfRuns Number of runs of the algorithm.
//     * @param stopCondition Type of stop condition.
//     * @param value Depending on stop condition either number of steps or minimal improvement.
//     * @return runResult After reaching stop condition it returns a structure containing all parameters required for further processing.
//     */
//    void run(int numberOfRuns, stopCondition condition, double value);

    /**
     * Removes unnecessary data structures.
     */
    virtual void clean();

    /**
     * Calculates cost for given permutation in O(n^2) time and returns it.
     * @param solution Optional pointer to solution to be rated; if not given, BaseAlgorithm::curSolution is used.
     * @return Cost of the solution.
     */
    int rateSolution(unsigned int* solution = NULL);

    /**
     * Calculates cost change from current solution to its neighbour in O(n) time.
     * @param id Index of neighbour to be rated, must be in range [0; BaseAlgorithm::neighbourhoodSize).
     * @return Calculated cost change.
     */
    int rateNeighbour(unsigned int id);

    /**
     * Generates only the id-th neighbour of the current solution.
     * @param id Index of the neighbour to be generated.
     * @return Pointer to the generated neighbour (same as BaseAlgorithm::neighbours[id]).
     */
    unsigned int* generateNeighbour(unsigned int id);

    /**
     * Generates all neighbours of current solution and stores them in neighbours.
     */
    void generateAllNeighbours();

    /**
     * Generates random permutation of current solution and stores it in BaseAlgorithm::randomSolution.
     */
    void generateRandomPermutation();

    unsigned int problemSize; /**< Given problem's size.*/
    unsigned int neighbourhoodSize; /**< Number of the possible neighbours for given solution size.*/
    unsigned int** neighbours; /**< Dynamically allocated array to store all neighbours of the current solution.*/
    /**
     * Two-dimensional array of ints describing which elements of the solution should be swapped to get n-th neighbour.
     * BaseAlgorithm::neighbourSwaps[n][0] is an index of the first element and BaseAlgorithm::neighbourSwaps[n][1] of the second.
     */
    unsigned int** neighbourSwaps;

    std::mt19937 randGen; /**< Marsenne Twister19937 normal random generator object.*/

//  Instead of old result structure
    unsigned int* curSolution; /**< Dynamically allocated space for current solution chosen.*/
    unsigned int* bestSolution; /**< Dynamically allocated space for best solution found thorough time of working.*/
    unsigned int* randomSolution; /**< Dynamically allocated space for random solutions generation.*/
    double workTime; /**< Time it took the algorithm to execute, in seconds.*/
    unsigned int numberOfSteps; /**< Numbers of steps to be executed (before starting algorithm) and no. of steps executed (after finishing algorithm).*/
    int curCost; /**< Cost of the current solution.*/
    int minCost; /**< Minimal cost during execution of this instance.*/
    int* historicalCosts; /**< Dynamically allocated array for remembering all calculated costs.*/

    int** A; /**< Array A of problem definition passed through constructor.*/
    int** B; /**< Array B of problem definition passed through constructor.*/
    bool isInitialised; /**< Helper property indicating if algorithm have been properly initialised.*/
};

#endif /* BASEALGORITHM_H_ */
