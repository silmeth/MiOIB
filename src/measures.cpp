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
// Current implementation is most general
// (asymmetric, distances and flows between selfs):
// If both are true, optimize for symmetric without counting for i == j
// (second for from j = i+1 and return res*2)
int rateSolution(int** A, int** B, int* solution, unsigned int sz) {
    int res = 0;
    for(unsigned int i = 0; i < sz; i++) {
        for(unsigned int j = 0; j < sz; j++) {
            res += A[i][j]*B[solution[i]][solution[j]];
        }
    }
    return res;
}

// TODO same as with rateSolution():
// think about optimizing for more special and less general problem
int rateChange(int** A, int** B, int* solution, unsigned int sz, unsigned int pos1, unsigned int pos2) {
    int res = 0;
    for(unsigned int i = 0; i < sz; i++) {
        // subtract previous elements
        res -= A[pos1][i]*B[solution[pos1]][solution[i]];
        res -= A[i][pos1]*B[solution[i]][solution[pos1]];
        res -= A[pos2][i]*B[solution[pos2]][solution[i]];
        res -= A[i][pos2]*B[solution[i]][solution[pos2]];

        // add new elements
        res += A[pos1][i]*B[solution[pos2]][solution[i]];
        res += A[i][pos1]*B[solution[i]][solution[pos2]];
        res += A[pos2][i]*B[solution[pos1]][solution[i]];
        res += A[i][pos2]*B[solution[i]][solution[pos1]];
    }
    return res;
}
