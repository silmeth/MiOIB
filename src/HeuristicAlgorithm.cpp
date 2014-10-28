/*
 * HeuristicAlgorithm.cpp
 *
 *  Created on: Oct 22, 2014
 *      Author: jacek
 */

#include "../inc/HeuristicAlgorithm.h"

HeuristicAlgorithm::HeuristicAlgorithm(int size, int** matA, int** matB, int seed) : BaseAlgorithm(size, matA, matB, seed) {

}

HeuristicAlgorithm::~HeuristicAlgorithm() {
    // TODO Auto-generated destructor stub
}

void HeuristicAlgorithm::run() {
    if(isInitialised) {
        result->lastPermutation = new unsigned int[problemSize];
        unsigned int* solution = result->lastPermutation;

        // Begin measuring time
        auto begin = std::chrono::high_resolution_clock::now();
        bool* isAUsed = new bool[problemSize];
        bool* isBUsed = new bool[problemSize];
        for(unsigned int i = 0; i < problemSize; i++) {
            isAUsed[i] = false;
            isBUsed[i] = false;
        }

        for(unsigned int k = 0; k < problemSize; k++) {
            bool first = true;
            int iAMax = 0;
            int jAMax = 0;
            int AMax = 0;
            int iBMin = 0;
            int jBMin = 0;
            int BMin = 0;
            for(unsigned int i = 0; i < problemSize; i++) {
                for(unsigned int j = 0; j < problemSize; j++) {
                    if(i != j) {
                        if(first) {
                            AMax = A[i][j];
                            iAMax = i;
                            jAMax = j;
                            BMin = B[i][j];
                            iBMin = i;
                            jBMin = j;
                            first = false;
                        } else {
                            if(A[i][j] > AMax && !isAUsed[i] && !isAUsed[j]) {
                                iAMax = i;
                                jAMax = j;
                            }
                            if(B[i][j] < BMin /* && !isBUsed[i] && !isBUsed[j]*/) {
                                iBMin = i;
                                jBMin = j;
                            }
                        }
                    }
                }
            }
            solution[iAMax] = iBMin;
            solution[jAMax] = jBMin;

            isAUsed[iAMax] = true;
            isAUsed[jAMax] = true;
            isBUsed[iBMin] = true;
            isBUsed[jBMin] = true;
        }
        auto end = std::chrono::high_resolution_clock::now();
        result->workTime = std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1e9;
        if(isAUsed) delete[] isAUsed;
        if(isBUsed) delete[] isBUsed;
        rateSolution();
        result->numberOfSteps = 1;
        result->historicalCosts = NULL;
        delete[] result->lastPermutation;
    }
}
