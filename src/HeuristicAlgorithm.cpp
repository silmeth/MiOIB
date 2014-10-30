/*
 * HeuristicAlgorithm.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: jacek, silmeth
 */

#include "../inc/HeuristicAlgorithm.h"

HeuristicAlgorithm::HeuristicAlgorithm(unsigned int size, int** matA, int** matB, int seed) : BaseAlgorithm(size, matA, matB, seed) {
    historicalCosts = nullptr;
}

HeuristicAlgorithm::~HeuristicAlgorithm() {

}

void HeuristicAlgorithm::run() {
    if(isInitialised) {
        // Begin measuring time
        auto begin = std::chrono::high_resolution_clock::now();
        bool* isAUsed = new bool[problemSize];
        bool* isBUsed = new bool[problemSize];
        for(unsigned int i = 0; i < problemSize; i++) {
            isAUsed[i] = false;
            isBUsed[i] = false;
        }

        for(unsigned int k = 0; k < problemSize; k++) {
            bool firstA = true;
            bool firstB = true;
            int iAMax = 0;
            int jAMax = 0;
            int AMax = 0;
            int iBMin = 0;
            int jBMin = 0;
            int BMin = 0;
            for(unsigned int i = 0; i < problemSize; i++) {
                for(unsigned int j = 0; j < problemSize; j++) {
                    if(i != j) {
                        if(firstA && !isAUsed[i] && !isAUsed[j]) {
                            AMax = A[i][j];
                            iAMax = i;
                            jAMax = j;
                            firstA = false;
                        } else if(!isAUsed[i] && !isAUsed[j] && A[i][j] > AMax) {
                            iAMax = i;
                            jAMax = j;
                        }
                        if(firstB && !isBUsed[i] && !isBUsed[j]) {
                                BMin = B[i][j];
                                iBMin = i;
                                jBMin = j;
                                firstB = false;
                        } else if(!isBUsed[i] && !isBUsed[j] && B[i][j] < BMin) {
                                iBMin = i;
                                jBMin = j;
                        }
                    }
                }
            }
            if(!firstA && !firstB) {
                curSolution[iAMax] = iBMin;
                curSolution[jAMax] = jBMin;

                isAUsed[iAMax] = true;
                isAUsed[jAMax] = true;
                isBUsed[iBMin] = true;
                isBUsed[jBMin] = true;
            }
        }
        auto end = std::chrono::high_resolution_clock::now();
        workTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1.e9;
        minCost = curCost = rateSolution();
        memcpy(bestSolution, curSolution, sizeof(unsigned int) * problemSize);
        numberOfSteps = 1;
        if(isAUsed) delete[] isAUsed;
        if(isBUsed) delete[] isBUsed;
    }
}
