/*
 * silmeth_test.cpp
 *
 *  Created on: Oct 18, 2014
 *      Author: silmeth
 */

#ifdef SILMETH_TEST // define SILMETH_TEST before compile to enable this file
#include <iostream>
#include <random>

#include "../inc/algorithms.h"
#include "../inc/instances.h"
#include "../inc/measures.h"
#include "../inc/operations.h"

void printSol(int* solution, unsigned int sz) {
    for(unsigned int i = 0; i < sz; i++) {
        std::cout << solution[i];
        if(i != sz-1)
            std::cout << ", ";
        else
            std::cout << std::endl;
    }
}

const unsigned int sz = 8;

int main() {
    const unsigned int neighSz = sz*(sz-1)/2; // every solution has exactly sz*(sz-1)/2 neighbours

    // allocating memory for solutions
    int* sol = new int[sz];
    int** neighbs = new int*[neighSz];
    for(unsigned int i = 0; i < neighSz; i++)
        neighbs[i] = new int[sz];
    int* permRnd1 = new int[sz];
    int* permRnd2 = new int[sz];
    int* permRnd3 = new int[sz];
    int* permRnd4 = new int[sz];

    // initializing values
    for(unsigned int i = 0; i < sz; i++)
        sol[i] = i;

    // uniform pseudorandom generator
    std::mt19937 mtGen(19910401);

    // test functions
    generateAllNeighbours(sol, neighbs, sz);
    generateRandomPermutation(sol, permRnd1, sz, mtGen);
    generateRandomPermutation(sol, permRnd2, sz, mtGen);
    generateRandomPermutation(sol, permRnd3, sz, mtGen);
    generateRandomPermutation(sol, permRnd4, sz, mtGen);

    // print results
    std::cout << "Original solution: ";
    printSol(sol, sz);
    std::cout << std::endl;

    std::cout << "Permutation #1: ";
    printSol(permRnd1, sz);
    std::cout << "Permutation #2: ";
    printSol(permRnd2, sz);
    std::cout << "Permutation #3: ";
    printSol(permRnd3, sz);
    std::cout << "Permutation #4: ";
    printSol(permRnd4, sz);
    std::cout << std::endl;

    std::cout << "All neighbours:" << std::endl;
    for(unsigned int i = 0; i < neighSz; i++) {
        std::cout << i << ": ";
        printSol(neighbs[i], sz);
    }

    // deallocating everything
    delete[] sol;
    delete[] permRnd1;
    delete[] permRnd2;
    delete[] permRnd3;
    delete[] permRnd4;
    for(unsigned int i = 0; i < neighSz; i++)
        delete[] neighbs[i];
    delete[] neighbs;
}


#endif // SILMETH_TEST
