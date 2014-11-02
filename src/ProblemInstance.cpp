/*
 * ProblemInstance.cpp
 *
 *  Created on: Oct 15, 2014
 */

#include "../inc/ProblemInstance.h"

ProblemInstance::ProblemInstance(const char* fileName) : A(nullptr), B(nullptr), problemSize(0), lowestCost(0) {
    const char whitespaces[]  = " \t\r\n\f";
//    const char whitespaces_and_punctuation[]  = " \t\r\n\f;,=";
    std::string line;

    // values to count parsed matrix elements
    unsigned int i = 0; // rows
    unsigned int j = 0; // cols, or elements in rows
    bool AParsed = false; // Is A matrix done?
    bool sizeSet = false;
    bool lowestCostSet = false;
    std::ifstream inputFile(fileName, std::ifstream::in);

    // temporary storage for matrix elements
    std::vector<unsigned int> vecTmp;

//    unsigned int lineCounter = 0;
    if(inputFile.is_open()) {
//        std::cout << "Reading problem " << fileName << std::endl;
        while(getline(inputFile, line)) {
            if(!sizeSet) {
                if(strtk::parse(line, whitespaces, vecTmp)) {
                    if(vecTmp.size() > 0) {
                        problemSize = vecTmp[0];
                        A = new int*[problemSize];
                        B = new int*[problemSize];
                        vecTmp.erase(vecTmp.begin());
                        sizeSet = true;
                    }
                }
            } else if(strtk::parse(line, whitespaces, vecTmp) && problemSize > 0) {
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
//            lineCounter++;
        }
        inputFile.close();
    }

    std::string fileNameStr(fileName);
    fileNameStr.replace(fileNameStr.end()-3, fileNameStr.end(), "sln");
    std::ifstream inputSolutionFile(fileNameStr.c_str(), std::ifstream::in);
    if(inputSolutionFile.is_open()) {
        while(getline(inputSolutionFile, line)) {
            if(!lowestCostSet) {
                if(strtk::parse(line, whitespaces, vecTmp)) {
                    if(vecTmp.size() > 1) {
                        lowestCost = vecTmp[1];
                        lowestCostSet = true;
                        vecTmp.clear();
                    }
                }
            }
        }
        inputSolutionFile.close();
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
