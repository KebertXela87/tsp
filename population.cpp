#include <iostream>
#include "population.h"
#include "tour.h"
#include "cities.h"

using namespace std;

Population::Population()
{
	for(int i = 0; i < tours.size(); i++)
	{
		Tour tour;
		tours[i] = tour;
	}
}

Tour Population::getTour(int index)
{
	return tours[index];
}

void Population::setTour(int index, Tour tour)
{
	tours[index] = tour;
}

int Population::getSize()
{
	return tours.size();
}

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
