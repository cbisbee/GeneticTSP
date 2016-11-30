#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <map>
#include <algorithm>
#include "Individual.h"
#include "City.h"
#include "Population.h"

bool ELITISM = true;
double MUTATIONRATE = 1;

void readData(std::map<int, City> &cityList)
{
	City initCity;
	initCity.setAll(0, -1, -1);
	cityList.insert(std::pair<int, City>(0, initCity));
	int name, x, y;

	std::ifstream fin("MapData.in");
	while (!fin.eof())
	{
		fin >> name >> x >> y;
		City newCity = City(name, x, y);
		cityList.insert(std::pair<int, City>(newCity.getName(), newCity));
	}
}

Individual tournamentSelection(Population pop)
{
	Individual selectedIndividual;
	int tournamentSize = TOURSIZE;

	Population tournament;

	for (int i = 0; i < tournamentSize; i++)
	{
		int randomID = rand() % TOURSIZE;
		tournament.addIndividualAt(i, pop.getIndividualAt(randomID));
	}
	
	selectedIndividual = tournament.getFittestIndividual();

	return selectedIndividual;
}

void mutate(Individual &curInd)
{
	//loop through individual
	for (int i = 0; i < TOURSIZE; i++)
	{
		//create a random number and check if it is less than to some constant mutation rate
		int randomnum = rand() & 100;
		if (randomnum < MUTATIONRATE)
		{
			//get a random position with the bounds of the individual
			int randompos = rand() % TOURSIZE;

			//swap the cities at i and at the random pos you found
			int temp = curInd.getCityAt(i);
			curInd.setCityAt(i, curInd.getCityAt(randompos));
			curInd.setCityAt(randompos, temp);
		}
	}
}

Individual crossover(Individual p1, Individual p2, std::map<int, City> mapData)
{
	int startPosP1 = rand() % TOURSIZE; //lower bound of p1 subtour
	int endPosP1 = rand() % TOURSIZE; //upper bound of p1 subtour
	std::vector<int> addedCities;
	int nump1 = 0, nump2 = 0;

	//if startPos and endPos are out of order then swap them around
	if (startPosP1 > endPosP1)
	{
		int temp = startPosP1;
		startPosP1 = endPosP1; 
		endPosP1 = temp;
	}

	Individual child; //creating new child

	//loop and add the subtour of p1 to child
	for (int i = startPosP1; i <= endPosP1; i++)
	{
			child.setCityAt(i, p1.getCityAt(i));
			addedCities.push_back(p1.getCityAt(i));
			nump1++;
	}


	//loop and add the cities from p2 that aren't already in child into any remaining spots in child until that bad boy is full
	for (int i = 0; i < TOURSIZE; i++)
	{
		int city = p2.getCityAt(i);
		//double checking to make sure the child doesn't already have the city
		if (!(child.containsCity(city)))
		//if(std::find(addedCities.begin(), addedCities.end(), city) == addedCities.end())
		{
			//finding empty spot in child to put city
			for (int j = 0; j < TOURSIZE; j++)
			{
				if (child.getCityAt(j) == -1) //ABSOLUTELY HAVE TO INITIALIZE ALL INDIVIDUALS TO -1!!!!!!!!
				{
					child.setCityAt(j, p2.getCityAt(i));
					//addedCities.push_back(city);
					nump2++;
					break;
				}
			}
		}
	}

	//return the new individual child
	return child;
}

Population evolve(Population pop, std::map<int, City> mapData)
{
	//create new population
	Population newPop;

	//determine whether or not you want eletism 
	int offset = 0;
	if (ELITISM)
	{
		offset++;
		newPop.addIndividualAt(0, pop.getIndividualAt(0));
	}

	for (int i = (0 + offset); i < TOURSIZE; i++)
	{
		//create two Individuals (p1 and p2) using roulette wheel or tournament selection
		Individual p1 = tournamentSelection(pop);
		Individual p2 = tournamentSelection(pop);
		//create a child Individual and set it equal to the crossover of p1 and p2
		Individual child = crossover(p1,p2,mapData);
		//add a bit of mutation to each individual
		mutate(child);
		child.setFitness(mapData);
		newPop.addIndividualAt(i, child);
	}

	//return the new population
	return newPop;
}

//TODO: Implement actual addition of generations in main, need to figure that logic out.
int main()
{
	int numGenerations = 20000;
	srand(time(NULL));
	std::map<int, City> mapData;
	readData(mapData);
	Population gen0 = Population(0);

	gen0.InitializePopulation(mapData);
	std::cout << "Initial population:" << std::endl;
	gen0.printPopulation();

	for (int i = 0; i < numGenerations; i++)
	{
		gen0 = evolve(gen0, mapData);
		gen0.setMinFitness();
		gen0.setMaxFitness();
		gen0.setAvgFitness();
		gen0.sortPopulationByFitness();
	}

	std::cout << std::endl << std::endl << std::endl;
	gen0.setGenerationNumber(numGenerations);
	gen0.printPopulation();
	Individual fittest = gen0.getFittestIndividual();
	std::cout << "Distance calculated: " << fittest.getCostOfTrip() << std::endl;

	std::cin.get();
	std::cin.get();

	return 0;
}