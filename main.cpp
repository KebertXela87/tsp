#include <iostream>
#include <fstream>
#include <regex>
#include <cstdlib>
#include <ctime>
#include "cities.h"
#include "population.h"
#include "genetic_algorithm.h"
#include "tour.h"

using namespace std;

bool isNumber(char number[]);
Tour getFittestTour(Cities givenCities, int generations);

int main( int argc, char *argv[] ) 
{
    srand(static_cast<uint32_t>(time(0)));
    
	//Read in the cities file
	if (argc != 3)
	{
		// Invalid number of arguments
		cout << "Invalid Arguments - usage: " << argv[0] << " <generations> <filename>" << endl;
		exit(1);
	}

    //Check generation argument
    if(!isNumber(argv[1]))
    {
        // Invalid <generations> argument
        cout << "Invalid <generations> argument - <generations> must be a Integer\n"
             << "usage: " << argv[0] << " <generations> <filename>" << endl;
        exit(1);
    }

    int generations = atoi(argv[1]);

    // Check filenmae argument
	char* filename = argv[2];

    if(!regex_match(filename, regex(".*\\.txt")))
    {
        cout << "Invalid <filename> argument - <filename> must be a file that eixists and ends in '.txt'.\n"
             << "usage: " << argv[0] << " <generations> <filename>" << endl;
        exit(1);
    }
    else
    {
        // read file into Cities object
    	Cities givenCities(filename);

        int THREADS = 8;
        
        Tour fitnessArray[THREADS];

        cout << "Thinking" << flush;

        // create multiple instances of the genetic algorithm
        #pragma omp parallel for num_threads(THREADS)
        for (int i = 0; i < THREADS; i++)
        {
            fitnessArray[i] = getFittestTour(givenCities, generations);
        }

        // find the fittest tour of the results
        int fittestTourNum = 0;
        double fittestTour = fitnessArray[0].getFitness(givenCities);
        for (int j = 1; j < THREADS; j++)
        {
            if (fitnessArray[j].getFitness(givenCities) < fittestTour)
            {
                fittestTourNum = j;
                fittestTour = fitnessArray[j].getFitness(givenCities);
            }
        }

        // print out fittest tour distance and path
        cout << "\nI'm Done!" << endl;
        cout << "Distance of Fittest Path: " << fittestTour << endl;

        for(int i = 0; i < 100; i++)
        {
            cout << fitnessArray[fittestTourNum].getCity(i);
            if(i != 99)
                cout << ", ";
        }
        cout << endl;
    }
	return 0;
}

/* function: getFittestTour
 *
 * creates a population and runs a genetic algorithm for a number of generations.
 *
 * returns the fittest Tour of the population
 */
Tour getFittestTour(Cities givenCities, int generations) 
{   
    // create new population
    Population *pop = new Population();

    double bestDistance = 0.0;
    int gen = 0;

    int count = 0;
    Genetic_Algorithm ga;
    for (int i = 0; i < generations; i++)
    {
        cout << "." << flush;

        // if after 50 generations, no new "best distance" is found - break
        if(count >= 50)
        {
            break;
        }
        
        ga.getNewPopulation(pop, givenCities);
        if(bestDistance == 0.0 || bestDistance > pop->getFittest(givenCities).getFitness(givenCities))
        {
            bestDistance = pop->getFittest(givenCities).getFitness(givenCities);
            count = 0;
        }

        count++;
        gen++;
    }

    Tour returnValue = pop->getFittest(givenCities);

    delete pop;

    return returnValue;
}

/* funtion: isNumber
 * 
 * checks a char array to see if it contains a number
 *
 * returns TRUE - char array contains only digits
 * returns FALSE - char array contains chars other than digits
 */
bool isNumber(char number[])
{
    if (number[0] == '-')
    {
        return false;
    }
    else
    {
        for(int i = 0; number[i] != 0; i++)
        {
            if(!isdigit(number[i]))
            {
                return false;
            }
        }
        return true;
    }
}
