#include <iostream>
#include <cmath>
#include "cities.h"

using namespace std;

/* Cities
 * reads in the file and inserts the city locations into an array
 */
Cities::Cities(const char* filename)
{
	ifstream file(filename);

	if(!file.is_open())
	{
		cout << "Could not open file\n" << endl;
		exit(1);
	}
	else
	{
		int i = 0;
		while(file >> x) {

			file >> y;

			cityLocations[i][0] = x;
			cityLocations[i][1] = y;
            cityLocations[i][2] = i + 1;

			i++;
		}
	}
}

/* getX
 * returns the X location of city at index
 */
double Cities::getX(int index) {
	return cityLocations[index][0];
}

/* getY
 * returns the Y location of city at index
 */
double Cities::getY(int index) {
	return cityLocations[index][1];
}

/* getNum
 * returns the city number at index
 */
int Cities::getNum(int index) {
    return cityLocations[index][2];
}

/* getDistance
 * calculates the distance from one city to another
 */
double Cities::getDistance(int index, int index2) 
{
	double xDistance = abs(getX(index) - getX(index2));
	double yDistance = abs(getY(index) - getY(index2));

	return sqrt(pow(xDistance, 2.0) + pow(yDistance, 2.0));
}
