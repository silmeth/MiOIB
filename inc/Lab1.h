/*
 * Lab1.h
 *
 *  Created on: 29.10.2014
 */

#ifndef LAB1_H_
#define LAB1_H_

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "../inc/ProblemInstance.h"

#include "../inc/HeuristicAlgorithm.h"
#include "../inc/RandomAlgorithm.h"
#include "../inc/SteepestAlgorithm.h"
#include "../inc/GreedyAlgorithm.h"

#include <boost/tuple/tuple.hpp>
#include "gnuplot-iostream.h"

/**
 * Requires libraries: -lboost_iostreams -lboost_system -lboost_filesystem
 */
class Lab1 {
public:
	Lab1();
	virtual ~Lab1();
	/**
	 * Dla różnych problemów 30 uruchomień dla różnych wielkości problemu
	 * Oś x to wielkości instancji
	 * Wykres 1: Najlepsze wyniki
	 *           Może być wykresem punktowym z połączonymi liniami.
	 * Wykres 2: Średnie wyniki i odchylenia standardowe.
	 * Wykres 3: Sredni surowy czas działania + odchylenia standardowe.
	 * Wykres 4: Jakość(czas). Wybór niezdominowanych instancji. Są jakieś chmurki punktów?
	 * Wykres 5: średnia liczba kroków algorytmu. Liczba ocenionych (przejrzanych) rozwiązań.
	 */
	void task2(void);
};

#endif /* LAB1_H_ */
