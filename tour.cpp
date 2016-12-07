#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include <omp.h>
#include "tour.h"

using namespace std;

Tour::Tour()
{
    for (int i = 0; i < tour.size(); i++)
    {
        tour[i] = i + 1; // 1 to 100
    }

    // random_shuffle(tour.begin(), tour.end());
    random_shuffle(begin(tour), end(tour));

    this->fitness = 0.0;
}

Tour::Tour(int nullConstructor)
{
    for (int i = 0; i < tour.size(); i++)
    {
        tour[i] = -1;
    }

    this->fitness = 0.0;
}

double Tour::getFitness(Cities cities)
{
    double tmpDistance = 0.0;

    #pragma omp parallel for schedule(guided) num_threads(8) reduction(+:tmpDistance)
    for (int i = 0; i < tour.size() - 1; i++)
    {
        tmpDistance += cities.getDistance(getCity(i), getCity(i + 1));
    }

    tmpDistance += cities.getDistance(getCity(99), getCity(0));

    this->fitness = tmpDistance;

    return this->fitness;
}

int Tour::getCity(int tourPosition)
{
    return tour[tourPosition];
}

void Tour::setCity(int tourPosition, int city)
{
    tour[tourPosition] = city;
}

int Tour::getSize()
{
    return tour.size();
}

bool Tour::checkPosition(int index)
{
    if (tour[index] == -1)
    {
        return true; // position empty
    }
    return false;
}
