/*
 * heuristicAlg.cpp
 *
 *  Created on: Oct 20, 2014
 *      Author: jacek
 */

#include "../inc/heuristicAlg.h"

bool* isUsed;

int* genSolution(int* solution) {
    isUsed = new bool[sz];
    for(unsigned int i = 0; i < sz; i++)
        isUsed[i] = false;

    for(unsigned int k = 0; k < sz; k++) {
        bool first = true;
        int iAMax = 0;
        int jAMax = 0;
        int AMax = 0;
        int iBMin = 0;
        int jBMin = 0;
        int BMin = 0;
        for(unsigned int i = 0; i < sz; i++) {
            for(unsigned int j = 0; j < sz; j++) {
                if(!isUsed[i] && !isUsed[j] && i != j) {
                    if(first) {
                        AMax = A[i][j];
                        iAMax = i;
                        jAMax = j;
                        BMin = B[i][j];
                        iBMin = i;
                        jBMin = j;
                        first = false;
                    } else {
                        if(A[i][j] > AMax) {
                            iAMax = i;
                            jAMax = j;
                        }
                        if(B[i][j] < BMin) {
                            iBMin = i;
                            jBMin = j;
                        }
                    }
                }
            }
        }
        solution[iAMax] = iBMin;
        solution[jBMax] = jBMin;

        isUsed[i] = true;
        isUsed[j] = true;
    }
    delete[] isUsed;
    return solution;
}
