#ifndef POPULATION_H
#define POPULATION_H

#include <array>
#include "tour.h"
#include "cities.h"
using namespace std;

class Population
{
public:
	Population();
	Tour getTour(int index);
	void setTour(int index, Tour tour);
	int getSize();
	Tour getFittest(Cities cities);

private:
	array<Tour, 10000> tours; // array of tours

};

#endif
