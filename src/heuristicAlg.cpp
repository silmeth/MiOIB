/*
 * heuristicAlg.cpp
 *
 *  Created on: Oct 20, 2014
 *      Author: silmeth
 */

#include "../inc/heuristicAlg.h"

int* heuritsticGenSolution(int* solution) {
    bool* isAUsed = new bool[size];
    bool* isBUsed = new bool[size];
    for(unsigned int i = 0; i < size; i++) {
        isAUsed[i] = false;
        isBUsed[i] = false;
    }

    for(unsigned int k = 0; k < size; k++) {
        bool first = true;
        int iAMax = 0;
        int jAMax = 0;
        int AMax = 0;
        int iBMin = 0;
        int jBMin = 0;
        int BMin = 0;
        for(unsigned int i = 0; i < size; i++) {
            for(unsigned int j = 0; j < size; j++) {
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
                        if(B[i][j] < BMin && !isBUsed[i] && !isBUsed[j]) {
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
    delete[] isAUsed;
    delete[] isBUsed;
    return solution;
}
