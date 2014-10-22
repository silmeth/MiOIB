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

#include "../inc/BaseAlgorithm.h"

void testBaseAlgorithm(){
	BaseAlgorithm b = BaseAlgorithm();
	assert(b.startPermutation == NULL);
	assert(b.result == NULL);

	b.init(5);
	assert(b.startPermutation != NULL);
	assert(b.result != NULL);
	assert(b.problemSize == 5);

	b.clean();
	assert(b.startPermutation == NULL);
	assert(b.result == NULL);
}

int main() {
	testBaseAlgorithm();
	std::cout << "BaseAlgorithm test:  OK" << std::endl;
}


#endif // SPUTNIK_TEST



