/*
 * silmeth_test.cpp
 *
 *  Created on: Oct 18, 2014
 *      Author: silmeth
 */

#ifdef SILMETH_TEST // define SILMETH_TEST before compile to enable this file
#include <iostream>
#include <chrono>

#include "../inc/ProblemInstance.h"

#include "../inc/BaseAlgorithm.h"
#include "../inc/HeuristicAlgorithm.h"
#include "../inc/RandomAlgorithm.h"
#include "../inc/SteepestAlgorithm.h"
#include "../inc/GreedyAlgorithm.h"

#include "../inc/Lab1.h"

const unsigned int size = 12;

int rateSol(int** A, int** B, unsigned int* solution, unsigned int sz) {
    int res = 0;
    for(unsigned int i = 0; i < sz; i++) {
        for(unsigned int j = 0; j < sz; j++) {
            res += A[i][j]*B[solution[i]][solution[j]];
        }
    }
    return res;
}

void printSol(unsigned int* solution, unsigned int sz) {
    for(unsigned int i = 0; i < sz; i++) {
        std::cout << solution[i]+1;
        if(i != sz-1)
            std::cout << ", ";
        else
            std::cout << std::endl;
    }
}

void printCosts(int* costs, unsigned int sz) {
    for(unsigned int i = 0; i < sz; i++) {
            std::cout << i << ": " << costs[i];
            if(i != sz-1)
                std::cout << ", ";
            else
                std::cout << std::endl;
    }
}

void testBaseAlgorithm(unsigned int size, int** A, int** B) {
    BaseAlgorithm b(size, A, B);
    assert(b.problemSize == size);

    unsigned int solution[] = {7,5,12,2,1,3,9,11,10,6,8,4};
    for(unsigned int i = 0; i < size; i++)
        solution[i]--; // because original solution starts with 1, not 0

    // neighbour 3: 0, 4
    // neighbour 33: 3, 7
    memcpy(b.curSolution, solution, sizeof(unsigned int) * size);
    std::cout << "Rating solution test: " << std::endl;
    std::cout << "Solution rating: " << b.rateSolution() << std::endl;
    std::cout << "Valid rating: " << rateSol(A, B, solution, size) << std::endl;
    std::cout << "Changed rating: " << b.rateSolution() + b.rateNeighbour(32) << std::endl;
    switchElements(solution, 3, 6);
    std::cout << "Valid changed rating: " << rateSol(A, B, solution, size) << std::endl << std::endl;

    b.clean();
}

void testHeuristicAlgorithm(unsigned int size, int** A, int** B) {
    HeuristicAlgorithm alg(size, A, B);
    alg.run();
    std::cout << "Heuristic solution: " << std::endl;
    printSol(alg.bestSolution, alg.problemSize);
    std::cout << "Heuristic solution cost: " << alg.minCost << std::endl;
    std::cout << "Heuristic tested cost: " << rateSol(A, B, alg.bestSolution, alg.problemSize) << std::endl;
    std::cout << "Time to find solution: " << alg.workTime << std::endl << std::endl;
}

void testRandomAlgorithm(unsigned int size, int** A, int** B) {
    RandomAlgorithm alg(size, A, B, 10);

    alg.run();
    std::cout << "RandomAlgorithm" << std::endl;
    std::cout << "Best solution: ";
    printSol(alg.bestSolution, alg.problemSize);
    if(alg.numberOfSteps < 100) {
        std::cout << "Costs: ";
        printCosts(alg.historicalCosts, alg.numberOfSteps);
    }
    std::cout << "Smallest cost: " << alg.minCost << std::endl;
    std::cout << "Random tested cost: " << rateSol(A, B, alg.bestSolution, alg.problemSize) << std::endl;
    std::cout << "Time to find solution: " << alg.workTime << std::endl << std::endl;
}

void testSteepestAlgorithm(unsigned int size, int** A, int** B) {
    SteepestAlgorithm alg(size, A, B, DEFINITE_NUM_OF_STEPS, 30);

    alg.run();
    std::cout << "Steepest solution: " << std::endl;
    printSol(alg.bestSolution, alg.problemSize);
    std::cout << "Steepest solution cost: " << alg.minCost << std::endl;
    std::cout << "Steepest tested cost: " << rateSol(A, B, alg.bestSolution, alg.problemSize) << std::endl;
    if(alg.numberOfSteps < 100) {
        std::cout << "Costs: ";
        printCosts(alg.historicalCosts, alg.numberOfSteps);
    }
    std::cout << "Steps to find solution: " << alg.numberOfSteps << std::endl;
    std::cout << "Time to find solution: " << alg.workTime << std::endl << std::endl;

    std::cout << "Repeated run of SteepestAlgorithm" << std::endl;

    alg.repeatedRun(200);
    std::cout << "Steepest solution: " << std::endl;
    printSol(alg.bestSolution, alg.problemSize);
    std::cout << "Steepest solution cost: " << alg.minCost << std::endl;
    if(alg.numberOfSteps < 100) {
        std::cout << "Costs: ";
        printCosts(alg.historicalCosts, alg.numberOfSteps);
    }
    std::cout << "Steps to find solution: " << alg.numberOfSteps << std::endl;
    std::cout << "Time to find solution: " << alg.workTime << std::endl << std::endl;
}

void testGreedyAlgorithm(unsigned int size, int** A, int** B) {
    GreedyAlgorithm alg(size, A, B, DEFINITE_NUM_OF_STEPS, 30);

    alg.run();
    std::cout << "Greedy solution: " << std::endl;
    printSol(alg.bestSolution, alg.problemSize);
    std::cout << "Greedy solution cost: " << alg.minCost << std::endl;
    std::cout << "Greedy tested cost: " << rateSol(A, B, alg.bestSolution, alg.problemSize) << std::endl;
    if(alg.numberOfSteps < 100) {
        std::cout << "Costs: ";
        printCosts(alg.historicalCosts, alg.numberOfSteps);
    }
    std::cout << "Steps to find solution: " << alg.numberOfSteps << std::endl;
    std::cout << "Time to find solution: " << alg.workTime << std::endl << std::endl;

    std::cout << "Repeated run of GreedyAlgorithm" << std::endl;

    alg.repeatedRun(200);
    std::cout << "Greedy solution: " << std::endl;
    printSol(alg.bestSolution, alg.problemSize);
    std::cout << "Greedy solution cost: " << alg.minCost << std::endl;
    if(alg.numberOfSteps < 100) {
        std::cout << "Costs: ";
        printCosts(alg.historicalCosts, alg.numberOfSteps);
    }
    std::cout << "Steps to find solution: " << alg.numberOfSteps << std::endl;
    std::cout << "Time to find solution: " << alg.workTime << std::endl << std::endl;
}

void testTimeMeasurement() {
    std::cout << "Test time measurement." << std::endl;
    auto begin = std::chrono::high_resolution_clock::now();
    int b;
    for(int i = 0; i < 1e8; i++) {
        b++;
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "1e8 iterations: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1e9 << "s" << std::endl;
    begin = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < 2*1e8; i++) {
            b++;
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << "2*1e8 iterations: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1e9 << "s" << std::endl << std::endl;
}

void testInstances() {
    const char input[] = "./qapdatsol/lipa50a.dat";
    ProblemInstance ins(input);
    std::cout << "Problem size: " << ins.problemSize << std::endl;
    std::cout << "A1,1 = " << ins.A[0][0] << std::endl;
    std::cout << "A10,8 = " << ins.A[9][7] << std::endl;
    std::cout << "B1,1 = " << ins.B[0][0] << std::endl;
    std::cout << "B6,8 = " << ins.B[5][7] << std::endl << std::endl;
}

int main() {
    ProblemInstance problem("./qapdatsol/chr15c.dat");

    int** A = problem.A;
    int** B = problem.B;
    unsigned int size = problem.problemSize;

//    testBaseAlgorithm(size, A, B);
    testHeuristicAlgorithm(size, A, B);
    testRandomAlgorithm(size, A, B);
    testSteepestAlgorithm(size, A, B);
    testGreedyAlgorithm(size, A, B);
    testTimeMeasurement();
    testInstances();

    Lab1 lab;
    lab.task2();
}
#endif // SILMETH_TEST
