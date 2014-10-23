/*
 * sputnik_test.cpp
 *
 *  Created on: Oct 20, 2014
 *      matAuthor: jacek
 */

#ifdef SPUTNIK_TEST // define SPUTNIK_TEST before compile to enable this file
#include <iostream>
#include <chrono>

#include "../inc/algorithms.h"
#include "../inc/instances.h"
#include "../inc/measures.h"
#include "../inc/operations.h"

#include "../inc/BaseAlgorithm.h"
#include "../inc/HeuristicAlgorithm.h"
#include "../inc/RandomAlgorithm.h"
#include "../inc/SteepestAlgorithm.h"

void printSol(unsigned int* solution, unsigned int sz) {
    for(unsigned int i = 0; i < sz; i++) {
        std::cout << solution[i];
        if(i != sz-1)
            std::cout << ", ";
        else
            std::cout << std::endl;
    }
}

void printCosts(unsigned int* costs, unsigned int sz) {
	for(unsigned int i = 0; i < sz; i++) {
	        std::cout << i << ": " << costs[i];
	        if(i != sz-1)
	            std::cout << ", ";
	        else
	            std::cout << std::endl;
	    }
}

void testBaseAlgorithm(){
	BaseAlgorithm b = BaseAlgorithm();
	assert(b.result == NULL);

	int** ptrA = new int* [2];
	int** ptrB = new int* [2];
	b.init(5, ptrA, ptrB);
	assert(b.result != NULL);
	assert(b.problemSize == 5);

	b.clean();
	assert(b.result == NULL);

	delete [] ptrA;
	delete [] ptrB;
	b.clean();
}

void testHeuristicAlgorithm(){
	int** A = new int* [12];
	int** B = new int* [12];
	for(int i = 0; i < 12; i++) {
		A[i] = new int [12];
		B[i] = new int [12];
		for(int k = 0; k < 12; k++){
			A[i][k] = 0;
			B[i][k] = 0;
		}
	}
	A[0][1] = A[1][0] = 90; A[0][2] = A[2][0] = 10; A[0][3] = A[3][0] = 23; A[0][4] = A[4][0] = 43;
	A[1][5] = A[5][1] = 88;
	A[2][6] = A[6][2] = 26; A[2][7] = A[7][2] = 16;
	A[5][8] = A[8][5] = 1;
	A[7][9] = A[9][7] = 96;
	A[8][10] = A[10][8] = 29;
	A[9][11] = A[11][9] = 37;
	B[0][1] = B[1][0] = 36; B[0][2] = B[2][0] = 54; B[0][3] = B[3][0] = 26; B[0][4] = B[4][0] = 59; B[0][5] = B[5][0] = 72; B[0][6] = B[6][0] = 9; B[0][7] = B[7][0] = 34; B[0][8] = B[8][0] = 79; B[0][9] = B[9][0] = 17; B[0][10] = B[10][0] = 46; B[0][11] = B[11][0] = 95;
	B[1][2] = B[2][1] = 73; B[1][3] = B[3][1] = 35; B[1][4] = B[4][1] = 90; B[1][5] = B[5][1] = 58; B[1][6] = B[6][1] = 30; B[1][7] = B[7][1] = 78; B[1][8] = B[8][1] = 35; B[1][9] = B[9][1] = 44; B[1][10] = B[10][1] = 79; B[1][11] = B[11][1] = 36;
	B[2][3] = B[3][2] = 21; B[2][4] = B[4][2] = 10; B[2][5] = B[5][2] = 97; B[2][6] = B[6][2] = 58; B[2][7] = B[7][2] = 66; B[2][8] = B[8][2] = 69; B[2][9] = B[9][2] = 61; B[2][10] = B[10][2] = 54; B[2][11] = B[11][2] = 63;
	B[3][4] = B[4][3] = 93; B[3][5] = B[5][3] = 12; B[3][6] = B[6][3] = 46; B[3][7] = B[7][3] = 40; B[3][8] = B[8][3] = 37; B[3][9] = B[9][3] = 48; B[3][10] = B[10][3] = 68; B[3][11] = B[11][3] = 85;
	B[4][5] = B[5][4] = 64; B[4][6] = B[6][4] = 5; B[4][7] = B[7][4] = 29; B[4][8] = B[8][4] = 76; B[4][9] = B[9][4] = 16; B[4][10] = B[10][4] = 5; B[4][11] = B[11][4] = 76;
	B[5][6] = B[6][5] = 96; B[5][7] = B[7][5] = 55; B[5][8] = B[8][5] = 38; B[5][9] = B[9][5] = 54; B[5][10] = B[10][5] = 0; B[5][11] = B[11][5] = 34;
	B[6][7] = B[7][6] = 83; B[6][8] = B[8][6] = 35; B[6][9] = B[9][6] = 11; B[6][10] = B[10][6] = 56; B[6][11] = B[11][6] = 37;
	B[7][8] = B[8][7] = 44; B[7][9] = B[9][7] = 12; B[7][10] = B[10][7] = 15; B[7][11] = B[11][7] = 80;
	B[8][9] = B[9][8] = 64; B[8][10] = B[10][8] = 39; B[8][11] = B[11][8] = 33;
	B[9][10] = B[10][9] = 70; B[9][11] = B[11][9] = 86;
	B[10][11] = B[11][10] = 18;

	HeuristicAlgorithm alg;
	alg.init(12, A, B);
	alg.run();
	alg.rateSolution();
	std::cout << "Heuristic solution: " << alg.result->cost << " " << std::endl;
	std::cout << "Time to find solution: " << alg.result->workTime << std::endl << std::endl;

	for(int i = 0; i < 12; i++) {
		delete [] A[i];
		delete [] B[i];
	}
	delete [] A;
	delete [] B;
	alg.clean();
}

void testRandomAlgorithm(){
	int** A = new int* [12];
	int** B = new int* [12];
	for(int i = 0; i < 12; i++) {
		A[i] = new int [12];
		B[i] = new int [12];
		for(int k = 0; k < 12; k++){
			A[i][k] = 0;
			B[i][k] = 0;
		}
	}
	A[0][1] = A[1][0] = 90; A[0][2] = A[2][0] = 10; A[0][3] = A[3][0] = 23; A[0][4] = A[4][0] = 43;
	A[1][5] = A[5][1] = 88;
	A[2][6] = A[6][2] = 26; A[2][7] = A[7][2] = 16;
	A[5][8] = A[8][5] = 1;
	A[7][9] = A[9][7] = 96;
	A[8][10] = A[10][8] = 29;
	A[9][11] = A[11][9] = 37;
	B[0][1] = B[1][0] = 36; B[0][2] = B[2][0] = 54; B[0][3] = B[3][0] = 26; B[0][4] = B[4][0] = 59; B[0][5] = B[5][0] = 72; B[0][6] = B[6][0] = 9; B[0][7] = B[7][0] = 34; B[0][8] = B[8][0] = 79; B[0][9] = B[9][0] = 17; B[0][10] = B[10][0] = 46; B[0][11] = B[11][0] = 95;
	B[1][2] = B[2][1] = 73; B[1][3] = B[3][1] = 35; B[1][4] = B[4][1] = 90; B[1][5] = B[5][1] = 58; B[1][6] = B[6][1] = 30; B[1][7] = B[7][1] = 78; B[1][8] = B[8][1] = 35; B[1][9] = B[9][1] = 44; B[1][10] = B[10][1] = 79; B[1][11] = B[11][1] = 36;
	B[2][3] = B[3][2] = 21; B[2][4] = B[4][2] = 10; B[2][5] = B[5][2] = 97; B[2][6] = B[6][2] = 58; B[2][7] = B[7][2] = 66; B[2][8] = B[8][2] = 69; B[2][9] = B[9][2] = 61; B[2][10] = B[10][2] = 54; B[2][11] = B[11][2] = 63;
	B[3][4] = B[4][3] = 93; B[3][5] = B[5][3] = 12; B[3][6] = B[6][3] = 46; B[3][7] = B[7][3] = 40; B[3][8] = B[8][3] = 37; B[3][9] = B[9][3] = 48; B[3][10] = B[10][3] = 68; B[3][11] = B[11][3] = 85;
	B[4][5] = B[5][4] = 64; B[4][6] = B[6][4] = 5; B[4][7] = B[7][4] = 29; B[4][8] = B[8][4] = 76; B[4][9] = B[9][4] = 16; B[4][10] = B[10][4] = 5; B[4][11] = B[11][4] = 76;
	B[5][6] = B[6][5] = 96; B[5][7] = B[7][5] = 55; B[5][8] = B[8][5] = 38; B[5][9] = B[9][5] = 54; B[5][10] = B[10][5] = 0; B[5][11] = B[11][5] = 34;
	B[6][7] = B[7][6] = 83; B[6][8] = B[8][6] = 35; B[6][9] = B[9][6] = 11; B[6][10] = B[10][6] = 56; B[6][11] = B[11][6] = 37;
	B[7][8] = B[8][7] = 44; B[7][9] = B[9][7] = 12; B[7][10] = B[10][7] = 15; B[7][11] = B[11][7] = 80;
	B[8][9] = B[9][8] = 64; B[8][10] = B[10][8] = 39; B[8][11] = B[11][8] = 33;
	B[9][10] = B[10][9] = 70; B[9][11] = B[11][9] = 86;
	B[10][11] = B[11][10] = 18;
	RandomAlgorithm alg;
	alg.init(12, A, B);

	alg.run(10);
	std::cout << "RandomAlgorithm" << std::endl;
	std::cout << "Best solution: ";
	printSol(alg.result->bestPermutation, alg.problemSize);
	if(alg.result->numberOfSteps < 1000) {
		std::cout << "Costs: ";
		printCosts(alg.result->historicalCosts, alg.result->numberOfSteps);
	}
	std::cout << "Smallest cost: " << alg.result->cost << std::endl;
	std::cout << "Time to find solution: " << alg.result->workTime << std::endl << std::endl;
	alg.clean();
}

void testSteepestAlgorithm(){
	int** A = new int* [12];
		int** B = new int* [12];
		for(int i = 0; i < 12; i++) {
			A[i] = new int [12];
			B[i] = new int [12];
			for(int k = 0; k < 12; k++){
				A[i][k] = 0;
				B[i][k] = 0;
			}
		}
		A[0][1] = A[1][0] = 90; A[0][2] = A[2][0] = 10; A[0][3] = A[3][0] = 23; A[0][4] = A[4][0] = 43;
		A[1][5] = A[5][1] = 88;
		A[2][6] = A[6][2] = 26; A[2][7] = A[7][2] = 16;
		A[5][8] = A[8][5] = 1;
		A[7][9] = A[9][7] = 96;
		A[8][10] = A[10][8] = 29;
		A[9][11] = A[11][9] = 37;
		B[0][1] = B[1][0] = 36; B[0][2] = B[2][0] = 54; B[0][3] = B[3][0] = 26; B[0][4] = B[4][0] = 59; B[0][5] = B[5][0] = 72; B[0][6] = B[6][0] = 9; B[0][7] = B[7][0] = 34; B[0][8] = B[8][0] = 79; B[0][9] = B[9][0] = 17; B[0][10] = B[10][0] = 46; B[0][11] = B[11][0] = 95;
		B[1][2] = B[2][1] = 73; B[1][3] = B[3][1] = 35; B[1][4] = B[4][1] = 90; B[1][5] = B[5][1] = 58; B[1][6] = B[6][1] = 30; B[1][7] = B[7][1] = 78; B[1][8] = B[8][1] = 35; B[1][9] = B[9][1] = 44; B[1][10] = B[10][1] = 79; B[1][11] = B[11][1] = 36;
		B[2][3] = B[3][2] = 21; B[2][4] = B[4][2] = 10; B[2][5] = B[5][2] = 97; B[2][6] = B[6][2] = 58; B[2][7] = B[7][2] = 66; B[2][8] = B[8][2] = 69; B[2][9] = B[9][2] = 61; B[2][10] = B[10][2] = 54; B[2][11] = B[11][2] = 63;
		B[3][4] = B[4][3] = 93; B[3][5] = B[5][3] = 12; B[3][6] = B[6][3] = 46; B[3][7] = B[7][3] = 40; B[3][8] = B[8][3] = 37; B[3][9] = B[9][3] = 48; B[3][10] = B[10][3] = 68; B[3][11] = B[11][3] = 85;
		B[4][5] = B[5][4] = 64; B[4][6] = B[6][4] = 5; B[4][7] = B[7][4] = 29; B[4][8] = B[8][4] = 76; B[4][9] = B[9][4] = 16; B[4][10] = B[10][4] = 5; B[4][11] = B[11][4] = 76;
		B[5][6] = B[6][5] = 96; B[5][7] = B[7][5] = 55; B[5][8] = B[8][5] = 38; B[5][9] = B[9][5] = 54; B[5][10] = B[10][5] = 0; B[5][11] = B[11][5] = 34;
		B[6][7] = B[7][6] = 83; B[6][8] = B[8][6] = 35; B[6][9] = B[9][6] = 11; B[6][10] = B[10][6] = 56; B[6][11] = B[11][6] = 37;
		B[7][8] = B[8][7] = 44; B[7][9] = B[9][7] = 12; B[7][10] = B[10][7] = 15; B[7][11] = B[11][7] = 80;
		B[8][9] = B[9][8] = 64; B[8][10] = B[10][8] = 39; B[8][11] = B[11][8] = 33;
		B[9][10] = B[10][9] = 70; B[9][11] = B[11][9] = 86;
		B[10][11] = B[11][10] = 18;
		SteepestAlgorithm alg;
		alg.init(12, A, B);
		alg.run(definiteNumberOfSteps, 50);
		std::cout << "Steepest solution: " << alg.result->cost << " " << std::endl;
		if(alg.result->numberOfSteps < 100) {
			std::cout << "Costs: ";
			printCosts(alg.result->historicalCosts, alg.result->numberOfSteps);
		}
		std::cout << "Steps to find solution: " << alg.result->numberOfSteps << std::endl;
		std::cout << "Time to find solution: " << alg.result->workTime << std::endl << std::endl;

		std::cout << "Repeated run of SteepestAlgorithm" << std::endl;
		alg.repeatedRun(200, definiteNumberOfSteps, 50);
		std::cout << "Steepest solution: " << alg.result->cost << " " << std::endl;
		if(alg.result->numberOfSteps < 100) {
			std::cout << "Costs: ";
			printCosts(alg.result->historicalCosts, alg.result->numberOfSteps);
		}
		std::cout << "Steps to find solution: " << alg.result->numberOfSteps << std::endl;
		std::cout << "Time to find solution: " << alg.result->workTime << std::endl << std::endl;
		alg.clean();
}

void testTimeMeasurement(){
	std::cout << "Test time measurement." << std::endl;
	auto begin = std::chrono::high_resolution_clock::now();
	int b;
	for(int i = 0; i < 1e8; i++) {
		b++;
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::cout << "1e8 iterations: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1e9 << "s" << std::endl;
	begin = std::chrono::high_resolution_clock::now();
	for(int i = 0; i < 2*1e8; i++) {
			b++;
		}
	end = std::chrono::high_resolution_clock::now();
	std::cout << "2*1e8 iterations: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count()/1e9 << "s" << std::endl << std::endl;
}

void testInstances(){
	const char* input = "/home/jacek/Studia/MioIB/workspace/qap/qapdatsol/chr12a.dat";
	readDataFile(input);
	delete input;
}

int main() {
	testBaseAlgorithm();
	testHeuristicAlgorithm();
	testRandomAlgorithm();
	testTimeMeasurement();
	testSteepestAlgorithm();
	testInstances();
}


#endif // SPUTNIK_TEST



