#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include "population.h"
#include "cities.h"
#include "tour.h"

class Genetic_Algorithm
{
public:
	Genetic_Algorithm();
	void getNewPopulation(Population * pop, Cities cities);
	Tour getParent(Population * pop, Cities cities);
	Tour crossover(Population * pop, Cities cities);
	void mutate(Tour tour, Cities cities);

private:
	int MAX_RANDOM;
	double MUTATE_PERCENTAGE;
	int THREADS;
};

#endif
