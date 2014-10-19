/*
 * operations.cpp
 *
 *  Created on: Oct 15, 2014
 *      Author: silmeth
 */

#include "../inc/operations.h"
#include <cassert>

unsigned int sz;
unsigned int neighSz;
int** neighbours;
int* permutation;
std::mt19937 randGen;


void opInit(unsigned int size, int seed) {
    sz = size;
    neighSz = sz*(sz-1)/2; // every solution has exactly sz*(sz-1)/2 neighbours

    neighbours = new int*[neighSz]; // allocating memory for all neighbours of given solution
    for(unsigned int i = 0; i < neighSz; i++)
        neighbours[i] = new int[sz];

    permutation = new int[sz]; // allocating memory for random permutation of given solution

    randGen.seed(seed); // uniform Marsenne Twister random generator seed
}

void switchElements(int* solution, unsigned int pos1, unsigned int pos2) {
    if(pos1 != pos2) {
        int tmp = solution[pos1];
        solution[pos1] = solution[pos2];
        solution[pos2] = tmp;
    }
}

int** generateAllNeighbours(int* solution) {
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

int* generateRandomPermutation(int* solution) {
// TODO merge two for loops into one to minimize data copying (cf. http://en.wikipedia.org/wiki/Random_permutation#Knuth_shuffles)
    for(unsigned int i = 0; i < sz; i++) { // create copy of solution
        permutation[i] = solution[i];
    }

    for(unsigned int i = 0; i < sz; i++) { // swap elements sz times to randomize solution
        std::uniform_int_distribution<unsigned int> dist(0, sz-i-1);
        switchElements(permutation, dist(randGen), sz-i-1);
//        switchElements(permutation, (rand() % (sz-i)), sz-i-1);
    }

    return permutation;
}

void opClear() {
    for(unsigned int i = 0; i < neighSz; i++)
        delete[] neighbours[i];
    delete[] neighbours;

    delete[] permutation;
}
