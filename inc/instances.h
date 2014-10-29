/*
 * instances.h
 *
 *  Created on: Oct 15, 2014
 *  Instances of very simple problems to speed up development.
 */

#ifndef INSTANCES_H_
#define INSTANCES_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../strtk/strtk.hpp"

struct instance {
    unsigned int** A;
    unsigned int** B;
    unsigned int problemSize;
    unsigned int lowestCost;
};

instance readDataFile(const char* fileName);

#endif /* INSTANCES_H_ */
