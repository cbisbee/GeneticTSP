#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <map>
#include "Individual.h"
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

Individual crossover(Individual indA, Individual indB, std::map<int,City> mapData)
{
	Individual newInd = Individual();
	//put the first 5 of chromA into newChrom, put the second 5 of chromB into newChrom...
	for (int i = 0; i < TOURSIZE; i++) {
		if ((i < 5) || (i >= 10 && i < 15) || (i >= 20))
			newInd.addCity(indA.getCity(i));
		else
			newInd.addCity(indB.getCity(i));
	}
	newInd.setFitness(mapData);
	return newInd;
}

//TODO: Implement actual addition of generations in main, need to figure that logic out.
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