/*
 * Lab1.h
 *
 *  Created on: 29.10.2014
 */

#ifndef LAB1_H_
#define LAB1_H_

#include <iostream>
#include <cstdio>
#include <string>
#include <vector>

#include "../inc/ProblemInstance.h"

#include "../inc/HeuristicAlgorithm.h"
#include "../inc/RandomAlgorithm.h"
#include "../inc/SteepestAlgorithm.h"
#include "../inc/GreedyAlgorithm.h"
#include "../inc/SimmulatedAnnealing.h"
#include "../inc/TabuSearchAlgorithm.h"

enum typeOfAlgorithm {
    GREEDY,
    STEEPEST,
    RANDOM,
    HEURISTIC,
    SIM_ANN,
    TABU
};

/**
 * Requires libraries: -lboost_iostreams -lboost_system -lboost_filesystem
 */
class Lab1 {
public:
    Lab1();
    virtual ~Lab1();
    /**
     * Number of repetitions to run algorithms.
     */
    int repetitions = 200;
    std::vector<std::string> problemNames;
    /**
     * Runs all four algorithms and collects data needen for plotting charts listed below.
     *
     * Chart 1: Quality = f(instance size). Max, mean and std dev range.
     * Chart 2: Operation time = f(instance size). Mean and std dev range.
     * Chart 3: Quality = f(operation time). 1 chart for 1 algorithm.
     * Chart 4: Step number = f(instance size). Only Greedy and Steepest.
     * Chart 5: Final solution cost = f(initial solution cost). Only Greedy and Steepest.
     * Chart 6: ?? Number of checked permutations. Only Greedy and Steepest.
     */
    void task(void);
    /**
     * Calculates mean of values in vector.
     * \param vec Input vector.
     * \return Mean of vector values.
     */
    double mean(std::vector<double> vec);
    /**
     * Calculates standard deviation of values in vector.
     * \param vec Input vector.
     * \return Mean of vector values.
     */
    double stdDev(std::vector<double> vec);
private:
    /**
     * Number of instances read from input files.
     */
    int numberOfInstances;
    /**
     * Path to instance file.
     */
    char input[50];
};

#endif /* LAB1_H_ */
