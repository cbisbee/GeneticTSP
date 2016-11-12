#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <map>
#include "Chromosome.h"
#include "City.h"
#include "Population.h"

void readData(std::map<int, City> &cityList)
{
	int name, x, y;

	std::ifstream fin("MapData.in");
	while (!fin.eof())
	{
		fin >> name >> x >> y;
		City newCity = City(name, x, y);
		cityList.insert(std::pair<int, City>(newCity.getName(), newCity));
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
	srand(time(NULL));
	std::map<int, City> mapData;
	readData(mapData);
	Population gen0 = Population(0);
	gen0.InitializePopulation(mapData);
	gen0.printPopulation();

	std::cin.get();
	std::cin.get();



	return 0;
}