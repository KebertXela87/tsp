#include <iostream>
#include <omp.h>
#include "genetic_algorithm.h"

using namespace std;

Genetic_Algorithm::Genetic_Algorithm()
{
	this->MAX_RANDOM = 10000;
	this->MUTATE_PERCENTAGE = 0.02;
	this->THREADS = 8;
}

void Genetic_Algorithm::getNewPopulation(Population * pop, Cities cities)
{
	pop->setTour(0, pop->getFittest(cities));

	#pragma omp parallel for schedule(guided) num_threads(THREADS)
	for (int i = 1; i < pop->getSize(); i++)
	{
		pop->setTour(i, crossover(pop, cities));
	}

	// #pragma omp parallel for schedule(guided) num_threads(THREADS)
	for(int i = 0; i < pop->getSize(); i++)
	{
		mutate(pop->getTour(i), cities);
	}
}

Tour Genetic_Algorithm::getParent(Population * pop, Cities cities)
{
	double fittestParent = 0.0;
	int fittestParentNumber = 0;
	double checkParent = 0.0;

	// grab 4 random tours from population
	for(int i = 0; i < 10; i++)
	{
		// get a random number between 0 and population size
		int num = rand() % pop->getSize();

		// grab the tour at that position in the population
		checkParent = pop->getTour(num).getFitness(cities);

		// if tour is better than current fittest tour, replace it
		if (checkParent < fittestParent || fittestParent == 0)
		{
			fittestParent = checkParent;
			fittestParentNumber = num;
		}
	}

	// return fittest tour as parent
	return pop->getTour(fittestParentNumber);
}

Tour Genetic_Algorithm::crossover(Population * pop, Cities cities)
{
	// get two random parent tours
	Tour parent1 = getParent(pop, cities);
	Tour parent2 = getParent(pop, cities);

	// create new child tour
	Tour child(0);

	// array to hold city numbers from parent1
	int cityNums[20] = {0};

	// get a random starting position
	int startpos = rand() % parent1.getSize();

	// get a random ending position (startpos + number between 5 and 20)
	int end = rand() % 15 + 5;
	int endpos = startpos + end;

	// if endpos is past end of array, set endpos to last element of array
	if (endpos > parent1.getSize() - 1)
	{
		endpos = parent1.getSize() - 1;
	}

	// put selected parent1 cities into child tour
	int j = 0;
	for (int i = 0; i < child.getSize(); i++)
	{
		if (i >= startpos && i <= endpos)
		{
			child.setCity(i, parent1.getCity(i));
			cityNums[j] = child.getCity(i);
			j++;
		}
	}

	// put unused cities from parent2 into child tour
	bool parent1City = false;
	for (int parentpos = 0; parentpos < parent2.getSize(); parentpos++)
	{
		parent1City = false;

		for (int l = 0; l < 20; l++)
		{
			if (parent2.getCity(parentpos) == cityNums[l])
			{
				parent1City = true;
			}
		}

		if (!parent1City)
		{
			for (int childpos = 0; childpos < child.getSize(); childpos++)
			{
				if (child.checkPosition(childpos)) // true if position is empty
				{
					child.setCity(childpos, parent2.getCity(parentpos));
					break;
				}
			}
		}
	}

	return child;
}

void Genetic_Algorithm::mutate(Tour tour, Cities cities)
{
	// cout << "------------------ Start of Tour Swap ------------------" << endl;
	// loop through each city in tour
	for (int i = 0; i < tour.getSize(); i++)
	{
		// get random number
		double randomnumber = rand() % this->MAX_RANDOM;

		// if random number 
		if(randomnumber < (this->MAX_RANDOM * this->MUTATE_PERCENTAGE))
		{
			int j = (int) rand() % tour.getSize();

			// swap cities
			// cout << "Swapping " << tour.getCity(i) << " and " << tour.getCity(j)
			// 	<< " Positions: " << i << " and " << j << endl;
			tour.setCity(j, tour.getCity(i));
			tour.setCity(i, tour.getCity(j));
		}
	}

	// cout << "Tour: " << tour.getFitness(cities) << endl;
}