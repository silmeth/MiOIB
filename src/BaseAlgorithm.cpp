/*
 * BaseAlgorithm.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: jacek
 */

#include "../inc/BaseAlgorithm.h"

void switchElements(unsigned int* solution, unsigned int pos1, unsigned int pos2) {
    if(pos1 != pos2) {
        int tmp = solution[pos1];
        solution[pos1] = solution[pos2];
        solution[pos2] = tmp;
    }
}

BaseAlgorithm::BaseAlgorithm(int size, int** matA, int** matB, int seed) : problemSize(size), neighbourhoodSize(size*(size-1)/2),
                randGen(seed), A(matA), B(matB) {
    assert(neighbourhoodSize == size*(size-1)/2);
    assert(size > 0);
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

    assert(matA != NULL);
    assert(matB != NULL);
    // TODO If seed not set in operations, set it here.

//    curSolution = new unsigned int[problemSize];
    randomSolution = new unsigned int[problemSize];

    result = new runResult;
    generateRandomPermutation();
    result->bestPermutation = randomSolution;
    result->lastPermutation = randomSolution;
    isInitialised = true;
}

BaseAlgorithm::~BaseAlgorithm() {
    clean();
}

void BaseAlgorithm::clean() {
    if(isInitialised) {
        if(result != NULL) {
            delete result;
            result = NULL;
        }

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

    //    if(curSolution) delete[] curSolution;
        if(randomSolution) delete[] randomSolution;
        isInitialised = false;
    }
}

int BaseAlgorithm::rateSolution(unsigned int* solution) {
    if(!solution) solution = result->lastPermutation;
    result->cost = 0;
    for(unsigned int i = 0; i < problemSize; i++) {
        for(unsigned int j = 0; j < problemSize; j++) {
            result->cost += A[i][j]*B[solution[i]][solution[j]];
        }
    }
    return result->cost;
}

int BaseAlgorithm::rateNeighbour(unsigned int id) {
    int res = 0;
    unsigned int pos1 = neighbourSwaps[id][0];
    unsigned int pos2 = neighbourSwaps[id][1];
    for(unsigned int i = 0; i < problemSize; i++) {
        // subtract previous elements
        res -= A[pos1][i]*B[result->lastPermutation[pos1]][result->lastPermutation[i]];
        res -= A[i][pos1]*B[result->lastPermutation[i]][result->lastPermutation[pos1]];
        res -= A[pos2][i]*B[result->lastPermutation[pos2]][result->lastPermutation[i]];
        res -= A[i][pos2]*B[result->lastPermutation[i]][result->lastPermutation[pos2]];

        // add new elements
        res += A[pos1][i]*B[result->lastPermutation[pos2]][result->lastPermutation[i]];
        res += A[i][pos1]*B[result->lastPermutation[i]][result->lastPermutation[pos2]];
        res += A[pos2][i]*B[result->lastPermutation[pos1]][result->lastPermutation[i]];
        res += A[i][pos2]*B[result->lastPermutation[i]][result->lastPermutation[pos1]];
    }
    return res;
}

void BaseAlgorithm::generateAllNeighbours() {
    unsigned int l = 0;
    for(unsigned int i = 0; i < problemSize; i++) {
        for(unsigned int j = i+1; j < problemSize; j++) {
            assert(i != j);
            // copy old solution to new location
            memcpy(neighbours[l], result->lastPermutation, sizeof(unsigned int)*problemSize);
            switchElements(neighbours[l], i, j);  // swap elements, creating permuted neighbour
            l++;
        }
    }
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
