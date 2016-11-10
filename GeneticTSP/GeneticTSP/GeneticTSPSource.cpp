#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include "Chromosome.h"
#include "City.h"

void readData(std::vector<City> &cityList)
{
	int name, x, y;

	std::ifstream fin("MapData.in");
	while (!fin.eof())
	{
		fin >> name >> x >> y;
		City newCity = City(name, x, y);
		cityList.push_back(newCity);
	}
}

Chromosome crossover(Chromosome chromA, Chromosome chromB)
{
	Chromosome newChrom = Chromosome();
	//perform crossover functions
	return newChrom;
}


int main()
{
	std::vector<City> cityList;
	readData(cityList);



	return 0;
}