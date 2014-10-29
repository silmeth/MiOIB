/*
 * instances.cpp
 *
 *  Created on: Oct 15, 2014
 */

#include "../inc/instances.h"

// According to DannyK answer http://stackoverflow.com/questions/53849/how-do-i-tokenize-a-string-in-c
// Gives error *** Error in `/home/jacek/Studia/MioIB/workspace/qap/Debug/qap': corrupted double-linked list: 0x00000000019f09b0 ***
// Error appears on line 18

// Reading problem size works fine for me (silmeth). Probably error connected to faulty filepath or file itself.

instance readDataFile(const char* fileName) {
    const char whitespaces[]  = " \t\r\n\f";
//    const char whitespaces_and_punctuation[]  = " \t\r\n\f;,=";
    instance inst;
    std::string line;
    std::cout << "Input file: " << fileName << std::endl;
    std::ifstream inputFile(fileName, std::ifstream::in);
    std::vector<std::string> firstLine;
    std::vector<std::string> matrixA;
    std::vector<std::string> matrixB;
    unsigned int problemSize = 0;
    unsigned int lineCounter = 0;
    if(inputFile.is_open()) {
        std::cout << "Reading problem " << fileName << std::endl;
        while(getline(inputFile, line)) {
            if(lineCounter == 0) {
                if(strtk::parse(line, whitespaces, firstLine)) {
                    problemSize = std::stoi(firstLine[0]);
                    std::cout << "Problem size: " << problemSize << std::endl;
                }
                lineCounter++;
            }
        }
        inputFile.close();
    }
    return inst;
}


