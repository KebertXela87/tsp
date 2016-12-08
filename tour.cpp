#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include <omp.h>
#include "tour.h"

using namespace std;

/* Tour
 * fill tour with index numbers that will be used to reference cities
 * shuffle the order of the index numbers
 */
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

/* Tour
 * fill tour with '-1' instead of index numbers to be used as an empty tour
 */
Tour::Tour(int nullConstructor)
{
    for (int i = 0; i < tour.size(); i++)
    {
        tour[i] = -1;
    }

    this->fitness = 0.0;
}

/* getFitness
 * return the fitness of the tour
 */
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

/* getCity
 * return the city number at the tour position
 */
int Tour::getCity(int tourPosition)
{
    return tour[tourPosition];
}

/* setCity
 * set the city number to the tour position
 */
void Tour::setCity(int tourPosition, int city)
{
    tour[tourPosition] = city;
}

/* getSize
 * return the size of the tour
 */
int Tour::getSize()
{
    return tour.size();
}

/* checkPosition
 * check to see if tour position is empty (-1)
 */
bool Tour::checkPosition(int index)
{
    if (tour[index] == -1)
    {
        return true; // position empty
    }
    return false;
}
