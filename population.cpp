#include <iostream>
#include "population.h"
#include "tour.h"
#include "cities.h"

using namespace std;

/* Population
 * loop through population size and fill it with tours
 */
Population::Population()
{
	for(int i = 0; i < tours.size(); i++)
	{
		Tour tour;
		tours[i] = tour;
	}
}

/* getTour
 * return the tour at index
 */
Tour Population::getTour(int index)
{
	return tours[index];
}

/* setTour
 * set the passed tour to the index of the population
 */
void Population::setTour(int index, Tour tour)
{
	tours[index] = tour;
}

/* getSize
 * get the population size
 */
int Population::getSize()
{
	return tours.size();
}

/* getFittest
 * get the fittest tour of the population
 */
Tour Population::getFittest(Cities cities)
{
	Tour fittest = tours[0];

	for (int i = 1; i < tours.size(); i++)
	{
		if(fittest.getFitness(cities) >= tours[i].getFitness(cities))
		{
			fittest = tours[i];
		}
	}

	return fittest;
}
