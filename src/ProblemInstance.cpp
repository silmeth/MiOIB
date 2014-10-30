/*
 * ProblemInstance.cpp
 *
 *  Created on: Oct 15, 2014
 */

#include "../inc/ProblemInstance.h"

ProblemInstance::ProblemInstance(const char* fileName) : A(nullptr), B(nullptr) {
    const char whitespaces[]  = " \t\r\n\f";
//    const char whitespaces_and_punctuation[]  = " \t\r\n\f;,=";
    std::string line;

    // values to count parsed matrix elements
    unsigned int i = 0; // rows
    unsigned int j = 0; // cols, or elements in rows
    bool AParsed = false; // Is A matrix done?

    std::ifstream inputFile(fileName, std::ifstream::in);

    // temporary storage for matrix elements
    std::vector<unsigned int> vecTmp;

    unsigned int lineCounter = 0;
    if(inputFile.is_open()) {
//        std::cout << "Reading problem " << fileName << std::endl;
        while(getline(inputFile, line)) {
            if(lineCounter == 0) {
                if(strtk::parse(line, whitespaces, problemSize)) {
                    A = new int*[problemSize];
                    B = new int*[problemSize];
                }
            } else if(strtk::parse(line, whitespaces, vecTmp)) {
                // Or old fashion way:
                // for(std::vector<unsigned int>::iterator n = vecTmp.begin()...
                for(unsigned int n : vecTmp) {
                    if(!AParsed) {
                        if(j == 0) A[i] = new int[problemSize];
                        A[i][j] = n;
                        if(++j >= problemSize) {
                            j = 0;
                            if(++i >= problemSize) {
                                i = 0;
                                AParsed = true;
                            }
                        }
                    } else if(i < problemSize) {
                        if(j == 0) B[i] = new int[problemSize];
                        B[i][j] = n;
                        if(++j >= problemSize) {
                            j = 0;
                            ++i;
                        }
                    }
                }
                vecTmp.clear();
            }
            lineCounter++;
        }
        inputFile.close();
    }
}

ProblemInstance::~ProblemInstance() {
    if(A) {
        for(unsigned int i = 0; i < problemSize; ++i)
            if(A[i]) delete[] A[i];
        delete[] A;
    }

    if(B) {
        for(unsigned int i = 0; i < problemSize; ++i)
            if(B[i]) delete[] B[i];
        delete[] B;
    }
}