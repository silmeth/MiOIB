/*
 * operations.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: silmeth
 */

#include "../inc/operations.h"
#include <cassert>
//#include <cstdlib>

void switchElements(int* solution, unsigned int pos1, unsigned int pos2) {
    if(pos1 != pos2) {
        int tmp = solution[pos1];
        solution[pos1] = solution[pos2];
        solution[pos2] = tmp;
    }
}

int** generateAllNeighbours(int* solution, int** neighbours, unsigned int sz) {
    unsigned int l = 0;
    for(unsigned int i = 0; i < sz; i++) {
        for(unsigned int j = i+1; j < sz; j++) {
            assert(i != j);
            for(unsigned int k = 0; k < sz; k++) // copy old solution to new location
                neighbours[l][k] = solution[k];
            switchElements(neighbours[l], i, j);  // swap elements, creating permuted neighbour
            l++;
        }
    }
    return neighbours;
}

int* generateRandomPermutation(int* solution, int* permutation, unsigned int sz, std::mt19937& randGen) {
    for(unsigned int i = 0; i < sz; i++) { // create copy of solution
        permutation[i] = solution[i];
    }

    // TODO: replace rand() with better C++ <random>
    for(unsigned int i = 0; i < sz; i++) { // swap elements sz times to randomize solution
        std::uniform_int_distribution<unsigned int> dist(0, sz-i-1);
        switchElements(permutation, dist(randGen), sz-i-1);
//        switchElements(permutation, (rand() % (sz-i)), sz-i-1);
    }

    return permutation;
}
