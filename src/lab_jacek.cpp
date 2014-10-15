//============================================================================
// Name        : main.cpp
// Author      : 
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <memory.h>
using namespace std;

inline int factorial(unsigned int n) // wersja rekurencyjna
{
   return (n < 1) ? 1 : n * factorial(n-1);
}

void swapElements(int **perm, int permNumber, int posElemA, int posElemB){
	int temp = perm[permNumber][posElemA];
	perm[permNumber][posElemA] = perm[permNumber][posElemB];
	perm[permNumber][posElemB] = temp;
}

int ** initializeAllNeighbours(int length, int *input){
	if(length < 2){
		cout << "Length is too small." << endl;
	}
	else{
		int ** permutations;
		int numberOfNeighbours = (length-1+0) * length / 2;
		permutations = new int *[numberOfNeighbours];
		for(int i = 0; i < numberOfNeighbours; i++){
			permutations[i] = new int[length];
			permutations[i][0] = 19;
			memcpy(permutations[i], input, sizeof(int)*length);
		}
		int counter = 0;
		for(int i = 0; i < length; i++){
			for(int k = i+1; k < length; k++){
				swapElements(permutations, counter, i, k);
				counter++;
			}
		}
		return permutations;
	}
}

void printAllNeighbours(int **permutations, int length){
	int numberOfPerm = (length+1) * length / 2;
	for(int i = 0; i < numberOfPerm; i++){
		cout << i << endl;
		for(int k = 0; k < length; k++){
			cout << permutations[i][k] << " ";
		}
		cout << endl;
	}
}

void clearArrays(int ** permutations, int length){
	int numberOfPerm = factorial(length);
	for (int i = 0; i << numberOfPerm; i++){
		delete [] permutations[i];
	}
}

int old_main() {
	cout << "Hello world" << endl; // prints
	int lengthOfInputSolution = 6;
	int inputSolution[6] = {1, 2, 3, 4, 5, 6};
	int ** permutations = initializeAllNeighbours(lengthOfInputSolution, inputSolution);
	printAllNeighbours(permutations, lengthOfInputSolution);
	clearArrays(permutations, lengthOfInputSolution);
	return 0;
}
