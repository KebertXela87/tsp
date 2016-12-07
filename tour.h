#ifndef TOUR_H
#define TOUR_H

#include <array>
#include "cities.h"

using namespace std;

class Tour
{
public:
    Tour();
    Tour(int nullConstructor);
    double getFitness(Cities cities);
    int getCity(int tourPosition);
    void setCity(int tourPosition, int city);
    int getSize();
	bool checkPosition(int index);

private:
    array<int, 100> tour;
    double fitness; // total distance of tour
};

#endif
