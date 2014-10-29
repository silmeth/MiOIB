/*
 * BaseAlgorithm.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: jacek, silmeth
 */

#include "../inc/BaseAlgorithm.h"

void switchElements(unsigned int* solution, unsigned int pos1, unsigned int pos2) {
    if(pos1 != pos2) {
        int tmp = solution[pos1];
        solution[pos1] = solution[pos2];
        solution[pos2] = tmp;
    }
}

void BaseAlgorithm::initHelp() {
    neighbours = new unsigned int*[neighbourhoodSize];
    neighbourSwaps = new unsigned int*[neighbourhoodSize];

    for(unsigned int i = 0; i < neighbourhoodSize; i++) {
        neighbours[i] = new unsigned int[problemSize];
        neighbourSwaps[i] = new unsigned int[2];
    }

    unsigned int l = 0;
    for(unsigned int i = 0; i < problemSize; i++) {
        for(unsigned int j = i+1; j < problemSize; j++) {
            neighbourSwaps[l][0] = i;
            neighbourSwaps[l][1] = j;
            l++;
        }
    }

    assert(A != NULL);
    assert(B != NULL);
    // TODO If seed not set in operations, set it here.

    randomSolution = new unsigned int[problemSize];
    curSolution = new unsigned int[problemSize];
    bestSolution = new unsigned int[problemSize];

    generateRandomPermutation();
    memcpy(curSolution, randomSolution, sizeof(unsigned int)*problemSize);
    memcpy(bestSolution, randomSolution, sizeof(unsigned int)*problemSize);

    isInitialised = true;
}

BaseAlgorithm::BaseAlgorithm(unsigned int size, int** matA, int** matB, int seed) : problemSize(size), neighbourhoodSize(size*(size-1)/2),
                randGen(seed), A(matA), B(matB) {
    assert(neighbourhoodSize == size*(size-1)/2);
    assert(size > 0);
    initHelp();
}

void BaseAlgorithm::init(unsigned int size, int** matA, int** matB, int seed) {
    clean();
    A = matA; B = matB; problemSize = size; randGen.seed(seed); neighbourhoodSize = size*(size-1)/2;
    assert(neighbourhoodSize == size*(size-1)/2);
    assert(size > 0);
    initHelp();
}

BaseAlgorithm::~BaseAlgorithm() {
    clean();
}

void BaseAlgorithm::clean() {
    if(isInitialised) {
        if(neighbours) {
            for(unsigned int i = 0; i < neighbourhoodSize; i++) {
                if(neighbours[i]) delete[] neighbours[i];
            }
            delete[] neighbours;
        }

        if(neighbourSwaps) {
            for(unsigned int i = 0; i < neighbourhoodSize; i++) {
                if(neighbourSwaps[i]) delete[] neighbourSwaps[i];
            }
            delete[] neighbourSwaps;
        }

        if(curSolution) delete[] curSolution;
        if(bestSolution) delete[] bestSolution;
        if(randomSolution) delete[] randomSolution;
        isInitialised = false;
    }
}

int BaseAlgorithm::rateSolution(unsigned int* solution) {
    if(!solution) solution = curSolution;
    int cost = 0;
    for(unsigned int i = 0; i < problemSize; i++) {
        for(unsigned int j = 0; j < problemSize; j++) {
            cost += A[i][j]*B[solution[i]][solution[j]];
        }
    }
    return cost;
}

int BaseAlgorithm::rateNeighbour(unsigned int id) {
    int diffCost = 0;
    unsigned int pos1 = neighbourSwaps[id][0];
    unsigned int pos2 = neighbourSwaps[id][1];
    for(unsigned int i = 0; i < problemSize; i++) {
        if(i == pos1) {
            // subtract previous elements
            diffCost -= A[pos1][pos1]*B[curSolution[pos1]][curSolution[pos1]];
            diffCost -= A[pos2][pos1]*B[curSolution[pos2]][curSolution[pos1]];
            diffCost -= A[pos1][pos2]*B[curSolution[pos1]][curSolution[pos2]];

            // add new elements
            diffCost += A[pos1][pos1]*B[curSolution[pos2]][curSolution[pos2]];
            diffCost += A[pos2][pos1]*B[curSolution[pos1]][curSolution[pos2]];
            diffCost += A[pos1][pos2]*B[curSolution[pos2]][curSolution[pos1]];
        } else if(i == pos2) {
            // subtract previous elements
            diffCost -= A[pos2][pos2]*B[curSolution[pos2]][curSolution[pos2]];

            // add new elements
            diffCost += A[pos2][pos2]*B[curSolution[pos1]][curSolution[pos1]];
        } else {
            diffCost -= A[pos1][i]*B[curSolution[pos1]][curSolution[i]];
            diffCost -= A[i][pos1]*B[curSolution[i]][curSolution[pos1]];
            diffCost -= A[pos2][i]*B[curSolution[pos2]][curSolution[i]];
            diffCost -= A[i][pos2]*B[curSolution[i]][curSolution[pos2]];

            // add new elements
            diffCost += A[pos1][i]*B[curSolution[pos2]][curSolution[i]];
            diffCost += A[i][pos1]*B[curSolution[i]][curSolution[pos2]];
            diffCost += A[pos2][i]*B[curSolution[pos1]][curSolution[i]];
            diffCost += A[i][pos2]*B[curSolution[i]][curSolution[pos1]];
        }
    }
    return diffCost;
}

void BaseAlgorithm::generateAllNeighbours() {
    unsigned int l = 0;
    for(unsigned int i = 0; i < problemSize; i++) {
        for(unsigned int j = i+1; j < problemSize; j++) {
            assert(i != j);
            // copy old solution to new location
            memcpy(neighbours[l], curSolution, sizeof(unsigned int)*problemSize);
            switchElements(neighbours[l], i, j);  // swap elements, creating permuted neighbour
            l++;
        }
    }
}

unsigned int* BaseAlgorithm::generateNeighbour(unsigned int id) {
    unsigned int pos1 = neighbourSwaps[id][0];
    unsigned int pos2 = neighbourSwaps[id][1];
    memcpy(neighbours[id], curSolution, sizeof(unsigned int)*problemSize);
    switchElements(neighbours[id], pos1, pos2);
    return neighbours[id];
}

void BaseAlgorithm::generateRandomPermutation() {
// TODO merge two for loops into one to minimize data copying (cf. http://en.wikipedia.org/wiki/Random_permutation#Knuth_shuffles)
    for(unsigned int i = 0; i < problemSize; i++) { // create copy of solution
        randomSolution[i] = i;
    }

    for(unsigned int i = 0; i < problemSize; i++) { // swap elements sz times to randomize solution
        std::uniform_int_distribution<unsigned int> dist(0, problemSize-i-1);
        switchElements(randomSolution, dist(randGen), problemSize-i-1);
    }
}
