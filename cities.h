#ifndef CITIES_H
#define CITIES_H

#include <iostream>
#include <fstream>
using namespace std;

class Cities
{
public:
	Cities(const char* filename);
	double getX(int index);
	double getY(int index);
    int getNum(int index);
    double getDistance(int index, int index2);
    
private:
	double cityLocations[100][3]; // 100 = num cities, 3 = x, y, city num
	double x;
	double y;
};

#endif
