/*
 * ProblemInstance.h
 *
 *  Created on: Oct 29, 2014
 */

#ifndef INSTANCES_H_
#define INSTANCES_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../strtk/strtk.hpp"


/**
 * Class for handling files and problem instances.
 */
class ProblemInstance {
private:
    ProblemInstance();
public:
    /**
     * Reads instance of a problem from file into memory.
     * @param filepath A path to the file with instance defined.
     */
    ProblemInstance(const char* filepath);
    virtual ~ProblemInstance(); /**< Simple destructor.*/
    unsigned int** A; /**< Pointer to memory where the A matrix is loaded.*/
    unsigned int** B; /**< Pointer to memory where the B matrix is loaded.*/
    unsigned int problemSize; /**< The size of a problem.*/
    unsigned int lowestCost; /**< Optimal solution cost (if present in a file).*/
};

#endif /* INSTANCES_H_ */
