/*
 * measures.cpp
 *
 *  Created on: Oct 19, 2014
 *      Author: silmeth
 */

#include "../inc/measures.h"

// TODO think about the problem:
// * is it symmetric or asymmetric?
// * do always A[i][i] == 0 and B[i][i] == 0?
// Current implementation is most general (asymmetric, distances and flows between selfs):
// If both are true, optimize for symmetric without counting for i == j
// (second for from j = i+1 and return res*2)
int rateSolution(int** A, int** B, int* solution, int sz) {
    int res = 0;
    for(int i = 0; i < sz; i++) {
        for(int j = 0; j < sz; j++) {
            res += A[i][j]*B[solution[i]][solution[j]];
        }
    }
    return res;
}

int rateChange() {

}
