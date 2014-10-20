/*
 * sputnik_test.cpp
 *
 *  Created on: Oct 20, 2014
 *      matAuthor: jacek
 */

#ifdef SPUTNIK_TEST // define SPUTNIK_TEST before compile to enable this file
#include <iostream>

#include "../inc/algorithms.h"
#include "../inc/instances.h"
#include "../inc/measures.h"
#include "../inc/operations.h"
#include "../inc/randomAlg.h"

int main() {
	unsigned sz = 10;
	int** matA;
	int** matB;
	int* p = new int[10];
	for(int i = 0; i < 10; i++) {
		p[i] = i;
	}
	opInit(sz, 19910401);
	matA = new int*[sz];
	for(unsigned int i = 0; i < sz; i++) {
		matA[i] = new int[sz];
		for(unsigned int j = 0; j < sz; j++) // for most of the values are zeroes
			matA[i][j] = 0;
	}

	matA[0][1] = matA[1][0] = 90; matA[0][2] = matA[2][0] = 10; matA[0][3] = matA[3][0] = 23; matA[0][4] = matA[4][0] = 43;
	matA[1][5] = matA[5][1] = 88;
	matA[2][6] = matA[6][2] = 26; matA[2][7] = matA[7][2] = 16;
	matA[5][8] = matA[8][5] = 1;
	matA[7][9] = matA[9][7] = 96;
	matA[8][10] = matA[10][8] = 29;
	matA[9][11] = matA[11][9] = 37;

	matB = new int*[sz];
	for(unsigned int i = 0; i < sz; i++) {
		matB[i] = new int[sz];
		matB[i][i] = 0; // diagonal to zeroes
	}

	matB[0][1] = matB[1][0] = 36; matB[0][2] = matB[2][0] = 54; matB[0][3] = matB[3][0] = 26; matB[0][4] = matB[4][0] = 59; matB[0][5] = matB[5][0] = 72; matB[0][6] = matB[6][0] = 9; matB[0][7] = matB[7][0] = 34; matB[0][8] = matB[8][0] = 79; matB[0][9] = matB[9][0] = 17; matB[0][10] = matB[10][0] = 46; matB[0][11] = matB[11][0] = 95;
	matB[1][2] = matB[2][1] = 73; matB[1][3] = matB[3][1] = 35; matB[1][4] = matB[4][1] = 90; matB[1][5] = matB[5][1] = 58; matB[1][6] = matB[6][1] = 30; matB[1][7] = matB[7][1] = 78; matB[1][8] = matB[8][1] = 35; matB[1][9] = matB[9][1] = 44; matB[1][10] = matB[10][1] = 79; matB[1][11] = matB[11][1] = 36;
	matB[2][3] = matB[3][2] = 21; matB[2][4] = matB[4][2] = 10; matB[2][5] = matB[5][2] = 97; matB[2][6] = matB[6][2] = 58; matB[2][7] = matB[7][2] = 66; matB[2][8] = matB[8][2] = 69; matB[2][9] = matB[9][2] = 61; matB[2][10] = matB[10][2] = 54; matB[2][11] = matB[11][2] = 63;
	matB[3][4] = matB[4][3] = 93; matB[3][5] = matB[5][3] = 12; matB[3][6] = matB[6][3] = 46; matB[3][7] = matB[7][3] = 40; matB[3][8] = matB[8][3] = 37; matB[3][9] = matB[9][3] = 48; matB[3][10] = matB[10][3] = 68; matB[3][11] = matB[11][3] = 85;
	matB[4][5] = matB[5][4] = 64; matB[4][6] = matB[6][4] = 5; matB[4][7] = matB[7][4] = 29; matB[4][8] = matB[8][4] = 76; matB[4][9] = matB[9][4] = 16; matB[4][10] = matB[10][4] = 5; matB[4][11] = matB[11][4] = 76;
	matB[5][6] = matB[6][5] = 96; matB[5][7] = matB[7][5] = 55; matB[5][8] = matB[8][5] = 38; matB[5][9] = matB[9][5] = 54; matB[5][10] = matB[10][5] = 0; matB[5][11] = matB[11][5] = 34;
	matB[6][7] = matB[7][6] = 83; matB[6][8] = matB[8][6] = 35; matB[6][9] = matB[9][6] = 11; matB[6][10] = matB[10][6] = 56; matB[6][11] = matB[11][6] = 37;
	matB[7][8] = matB[8][7] = 44; matB[7][9] = matB[9][7] = 12; matB[7][10] = matB[10][7] = 15; matB[7][11] = matB[11][7] = 80;
	matB[8][9] = matB[9][8] = 64; matB[8][10] = matB[10][8] = 39; matB[8][11] = matB[11][8] = 33;
	matB[9][10] = matB[10][9] = 70; matB[9][11] = matB[11][9] = 86;
	matB[10][11] = matB[11][10] = 18;
	algInit(10, A, B, p);
	runResult result = randomAlg();
	std::cout << "Permutation:";
	for(int i = 0; i < sz; i++) {
		std::cout << " " << p[i];
	}
	std::cout << std::endl << "Cost: " << result.cost << ", # of steps: " << result.numberOfSteps << std::endl;
	opClear();
}


#endif // SPUTNIK_TEST



