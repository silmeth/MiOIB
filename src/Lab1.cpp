/*
 * Lab1.cpp
 *
 *  Created on: 29.10.2014
 *      Author: jacek
 */

#include "../inc/Lab1.h"

Lab1::Lab1() {
    // TODO Auto-generated constructor stub
	numberOfInstances = 0;
}

Lab1::~Lab1() {

}

void Lab1::task() {
    problemNames.push_back("chr12a");
    problemNames.push_back("chr15a");
    problemNames.push_back("chr18a");
    problemNames.push_back("chr20a");
    problemNames.push_back("chr22a");
    problemNames.push_back("chr25a");
    problemNames.push_back("bur26a");
    problemNames.push_back("els19");
    problemNames.push_back("esc16a");
    problemNames.push_back("esc32g");
    problemNames.push_back("kra30a");
    problemNames.push_back("had14");
    problemNames.push_back("nug17");
    problemNames.push_back("nug21");
    numberOfInstances = problemNames.size();

    ProblemInstance** instances;
    instances = new ProblemInstance* [numberOfInstances];
    for(int i = 0; i < numberOfInstances; i++) {
        sprintf(input, "./qapdatsol/%s.dat", problemNames.at(i).c_str());
        instances[i] = new ProblemInstance(input);
    }

    // Costs of best solutions found by each algorithm for each instance
    double** solutionBest;
    // Std dev of costs of solutions found by each algorithm for each instance
    double** solutionStdDev;
    // Means of costs of solutions found by each algorithm for each instance
    double** solutionMeans;
    // Std dev of worktime spent by each algorithm on each instance
    double** workTimeStdDev;
    // Means of worktime spent by each algorithm on each instance
    double** workTimeMeans;
    // Number of steps done for each instance (will depend on the number of repetitions)
    unsigned int** numberOfSteps;
    solutionBest = new double* [numberOfInstances];
    solutionStdDev = new double* [numberOfInstances];
    solutionMeans = new double* [numberOfInstances];
    workTimeStdDev = new double* [numberOfInstances];
    workTimeMeans = new double* [numberOfInstances];
    numberOfSteps = new unsigned int* [numberOfInstances];
    for(int i = 0; i < numberOfInstances; ++i) {
        // 3 is sum of Steepes, Greedy and Random
        solutionBest[i] = new double [4];
        solutionStdDev[i] = new double [3];
        solutionMeans[i] = new double [3];
        workTimeStdDev[i] = new double [3];
        workTimeMeans[i] = new double [4];
        numberOfSteps[i] = new unsigned int [2];
    }

    for(int i = 0; i < numberOfInstances; ++i) {
        RandomAlgorithm randAlg(instances[i]->problemSize, instances[i]->A, instances[i]->B, 30);
        SteepestAlgorithm steepAlg(instances[i]->problemSize, instances[i]->A, instances[i]->B, DEFINITE_NUM_OF_STEPS, 30);
        GreedyAlgorithm greedyAlg(instances[i]->problemSize, instances[i]->A, instances[i]->B, DEFINITE_NUM_OF_STEPS, 30);
        HeuristicAlgorithm heurAlg(instances[i]->problemSize, instances[i]->A, instances[i]->B);
        std::vector<double> randAlgCosts;
        std::vector<double> steepAlgCosts;
        std::vector<double> steepAlgInitCosts;
        std::vector<double> steepAlgNumberOfSteps;
        std::vector<double> steepAlgWorkTime;
        std::vector<double> greedyAlgCosts;
        std::vector<double> greedyAlgInitCosts;
        std::vector<double> greedyAlgNumberOfSteps;
        std::vector<double> greedyAlgWorkTime;

        heurAlg.run();

        randAlg.run();
        for(unsigned int j = 0; j < randAlg.numberOfSteps; ++j) {
            randAlgCosts.push_back((double)instances[i]->lowestCost / (double)randAlg.historicalCosts[j]);
        }

        for(int j = 0; j < repetitions; ++j) {
            // Ugly use of memcpy(), we should change run() method of each algorithm
            steepAlg.generateRandomPermutation();
            memcpy(steepAlg.curSolution, steepAlg.randomSolution, sizeof(unsigned int) * steepAlg.problemSize);
            steepAlgInitCosts.push_back(steepAlg.rateSolution());
            steepAlg.run();
            steepAlgCosts.push_back((double)instances[i]->lowestCost / steepAlg.minCost);
            steepAlgWorkTime.push_back(steepAlg.workTime);
            steepAlgNumberOfSteps.push_back(steepAlg.numberOfSteps);

            greedyAlg.generateRandomPermutation();
            memcpy(greedyAlg.curSolution, greedyAlg.randomSolution, sizeof(unsigned int) * greedyAlg.problemSize);
            greedyAlgInitCosts.push_back(greedyAlg.rateSolution());
            greedyAlg.run();
            greedyAlgCosts.push_back((double)instances[i]->lowestCost / greedyAlg.minCost);
            greedyAlgWorkTime.push_back(greedyAlg.workTime);
            greedyAlgNumberOfSteps.push_back(greedyAlg.numberOfSteps);
        }

        solutionBest[i][GREEDY] = *std::max_element(greedyAlgCosts.begin(), greedyAlgCosts.end());
        solutionBest[i][STEEPEST] = *std::max_element(steepAlgCosts.begin(), steepAlgCosts.end());
        solutionBest[i][RANDOM] = *std::max_element(randAlgCosts.begin(), randAlgCosts.end());
        solutionBest[i][HEURISTIC] = (double)instances[i]->lowestCost / heurAlg.minCost;
        solutionStdDev[i][GREEDY] = stdDev(greedyAlgCosts);
        solutionStdDev[i][STEEPEST] = stdDev(steepAlgCosts);
        solutionStdDev[i][RANDOM] = stdDev(randAlgCosts);
        solutionMeans[i][GREEDY] = mean(greedyAlgCosts);
        solutionMeans[i][STEEPEST] = mean(steepAlgCosts);
        solutionMeans[i][RANDOM] = mean(randAlgCosts);
        workTimeStdDev[i][GREEDY] = stdDev(greedyAlgWorkTime);
        workTimeStdDev[i][STEEPEST] = stdDev(steepAlgWorkTime);
        workTimeStdDev[i][RANDOM] = 0.0;
        workTimeMeans[i][GREEDY] = mean(greedyAlgWorkTime);
        workTimeMeans[i][STEEPEST] = mean(steepAlgWorkTime);
        workTimeMeans[i][RANDOM] = randAlg.workTime / (double)repetitions;
        workTimeMeans[i][HEURISTIC] = heurAlg.workTime;
        numberOfSteps[i][GREEDY] = mean(greedyAlgNumberOfSteps) * repetitions; // Because I'm to lazy to sum it in loop
        numberOfSteps[i][STEEPEST] = mean(steepAlgNumberOfSteps) * repetitions;
    }

    std::vector< std::vector<double> > solutionBestVec;
    std::vector< std::vector<double> > meanSolutionsVec;
    std::vector< std::vector<double> > stdDevSolutionsVec;
    std::vector<double> instanceSizeVec;

    for(unsigned int i = 0; i < 4; ++i) {
        std::vector<double> bestSolTmp;
        std::vector<double> meanSolTmp;
        std::vector<double> stdDevSolTmp;
        for(unsigned int j = 0; j < numberOfInstances; j++) {
            bestSolTmp.push_back(solutionBest[j][i]);
            if(i < 3) {
                meanSolTmp.push_back(solutionMeans[j][i]);
                stdDevSolTmp.push_back(solutionStdDev[j][i]);
            } else {
                instanceSizeVec.push_back((double)instances[j]->problemSize); // pure black magic, do not bother, keep scrolling
            }
        }

        solutionBestVec.push_back(bestSolTmp);
        meanSolutionsVec.push_back(meanSolTmp);
        stdDevSolutionsVec.push_back(stdDevSolTmp);
    }
    // Shiiiit starts right here

    // !!! Sample gnuplot script !!!
//    set term qt persist
//
//    set yrange [0:1]
//    set xrange [12:32]
//
//    set xtics 4
//    set ytics 0.2
//
//    set mxtics 4 # 4 minor tics between main x tics (each 1 unit)
//    set mytics 2 # 2 minor tics between main y tics (each 0.1 unit)
//
//    set key below # the legend under the plot, outside of plotting area
//
//    set format x "$%g$"
//    set format y "\\num{%.1f}" # \num{0.1} to be used with siunitx package
//
//    set xlabel "rozmiar problemu" # Polish for 'problem size'
//    set ylabel "jakość"           # Polish for 'quality'
//
//    set grid xtics ytics mxtics mytics ls 1 lw 1.7 linecolor rgbcolor "#8b8989", lw 0.7 lc rgbcolor "#8b8989"
//
//    plot "/tmp/randomData" using 1:3:4 title "random" with yerrorbars linecolor rgb "black" pointtype 6, \
//         "/tmp/randomData" using 1:2 title "" with points linecolor rgb "black" pointtype 7, \
//         "/tmp/greedyData" using 1:3:4 title "greedy" with yerrorbars linecolor rgb "red" pointtype 6, \
//         "/tmp/greedyData" using 1:2 title "" with points linecolor rgb "red" pointtype 7, \
//         "/tmp/steepestData" using 1:3:4 title "steepest" with yerrorbars linecolor rgb "green" pointtype 6, \
//         "/tmp/steepestData" using 1:2 title "" with points linecolor rgb "green" pointtype 7, \
//         "/tmp/heuristicData" using 1:2 title "heuristic" with points linecolor rgb "blue" pointtype 6
//
//    set term epslatex color size 15cm, 10cm
//    set output "/tmp/allAlgorithmsPlot.tex"
//    replot

    std::ofstream randomDataFile;
    std::ofstream greedyDataFile;
    std::ofstream steepestDataFile;
    std::ofstream heuristicDataFile;
    randomDataFile.open("/tmp/randomData", std::ios::out);
    greedyDataFile.open("/tmp/greedyData", std::ios::out);
    steepestDataFile.open("/tmp/steepestData", std::ios::out);
    heuristicDataFile.open("/tmp/heuristicData", std::ios::out);

    for(unsigned int i = 0; i < numberOfInstances; i++) {
        randomDataFile << instanceSizeVec[i] << " "
                       << solutionBestVec[RANDOM][i] << " "
                       << meanSolutionsVec[RANDOM][i] << " "
                       << stdDevSolutionsVec[RANDOM][i] << " "
                       << workTimeMeans[i][RANDOM] << " "
                       << workTimeStdDev[i][RANDOM] << std::endl;

        greedyDataFile << instanceSizeVec[i] << " "
                       << solutionBestVec[GREEDY][i] << " "
                       << meanSolutionsVec[GREEDY][i] << " "
                       << stdDevSolutionsVec[GREEDY][i] << " "
                       << workTimeMeans[i][GREEDY] << " "
                       << workTimeStdDev[i][GREEDY] << " "
                       << numberOfSteps[i][GREEDY] << std::endl;

        steepestDataFile << instanceSizeVec[i] << " "
                       << solutionBestVec[STEEPEST][i] << " "
                       << meanSolutionsVec[STEEPEST][i] << " "
                       << stdDevSolutionsVec[STEEPEST][i] << " "
                       << workTimeMeans[i][STEEPEST] << " "
                       << workTimeStdDev[i][STEEPEST] << " "
                       << numberOfSteps[i][STEEPEST] << std::endl;

        heuristicDataFile << instanceSizeVec[i] << " "
                       << solutionBestVec[HEURISTIC][i] << " "
                       << workTimeMeans[i][HEURISTIC] << std::endl;
    }

    randomDataFile.close();
    greedyDataFile.close();
    steepestDataFile.close();
    heuristicDataFile.close();

    //unsigned int size, int** matA, int** matB, unsigned int numberOfRuns, int seed=19910401
    for(int i = 0; i < numberOfInstances; ++i) {
        delete [] solutionBest[i];
        delete [] solutionStdDev[i];
        delete [] solutionMeans [i];
        delete []  workTimeStdDev[i];
        delete [] workTimeMeans[i];
        delete [] numberOfSteps[i];
        delete instances[i];
    }
    delete [] solutionBest;
    delete [] solutionStdDev;
    delete [] solutionMeans;
    delete [] instances;
    delete []  workTimeStdDev;
    delete [] workTimeMeans;
    delete [] numberOfSteps;

}

double Lab1::mean(std::vector<double> vec) {
    double sum = 0.0;
    for(std::vector<double>::iterator it = vec.begin(); it != vec.end(); ++it) {
        sum += *it;
    }
    return sum / (double)vec.size();
}

double Lab1::stdDev(std::vector<double> vec) {
    double sum = 0.0;
    double mn = mean(vec);
    for(std::vector<double>::iterator it = vec.begin(); it != vec.end(); ++it) {
        sum += pow(*it - mn, 2.0);
    }
    return sqrt(sum / (double)(vec.size()-1));
}
