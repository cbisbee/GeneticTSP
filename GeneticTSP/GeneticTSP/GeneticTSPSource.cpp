#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <map>
#include "Individual.h"
#include "City.h"
#include "Population.h"

bool ELITISM = false;
double MUTATIONRATE = 25;

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
		int randomNum = rand() & 100;
		if (randomNum < MUTATIONRATE)
		{
			//get a random position with the bounds of the individual
			int randomPos = rand() % TOURSIZE;

			//swap the cities at i and at the random pos you found
			int temp = curInd.getCityAt(i);
			curInd.setCityAt(i, curInd.getCityAt(randomPos));
			curInd.setCityAt(randomPos, temp);
		}
	}
}

Individual crossover(Individual p1, Individual p2, std::map<int, City> mapData)
{
	int startPos = rand() % TOURSIZE; //lower bound of p1 subtour
	int endPos = rand() % TOURSIZE; //upper bound of p1 subtour

	//if startPos and endPos are out of order then swap them around
	if (startPos > endPos)
	{
		int temp = startPos;
		startPos = endPos; 
		endPos = temp;
	}

	Individual child; //creating new child

	//loop and add the subtour of p1 to child
	for (int i = 0; i < TOURSIZE; i++)
	{
		if (i < endPos && i > startPos) //DO I NEED A LESS THAN OR EQUAL OR GREATER THAN OR EQUAL
			child.setCityAt(i, p1.getCityAt(i));
	}

	//loop and add the cities from p2 that aren't already in child into any remaining spots in child until that bad boy is full
	for (int i = 0; i < TOURSIZE; i++)
	{
		//double checking to make sure the child doesn't already have the city
		if (!child.containsCity(p2.getCityAt(i)))
		{
			//finding empty spot in child to put city
			for (int j = 0; j < TOURSIZE; j++)
			{
				if (child.getCityAt(j) == -1) //ABSOLUTELY HAVE TO INITIALIZE ALL INDIVIDUALS TO -1!!!!!!!!
				{
					child.setCityAt(j, p2.getCityAt(j));
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

	//determine whether or not oyu want eletism 
	int offset = 0;
	if (ELITISM)
	{
		offset++;
		newPop.addIndividualAt(0, pop.getIndividualAt(0));
	}

	for (int i = (0 + offset); i < (TOURSIZE - offset); i++)
	{
		//create two Individuals (p1 and p2) using roulette wheel or tournament selection
		Individual p1 = tournamentSelection(pop);
		Individual p2 = tournamentSelection(pop);
		//create a child Individual and set it equal to the crossover of p1 and p2
		Individual child = crossover(p1,p2,mapData);
		//add a bit of mutation to each individual
		mutate(child);
		newPop.addIndividualAt(i, child);
	}

	//return the new population
	return newPop;
}

//TODO: Implement actual addition of generations in main, need to figure that logic out.
int main()
{
	srand(time(NULL));
	std::map<int, City> mapData;
	readData(mapData);
	Population gen0 = Population(0);
	Population gen1(1);
	Population gen2(2);
	Population gen3(3);
	Population gen4(4);
	Population gen5(5);
	Population gen6(6);
	Population gen7(7);
	Population gen8(8);
	Population gen9(9);

	gen0.InitializePopulation(mapData);
	gen0.printPopulation();

	gen1 = evolve(gen0, mapData);
	std::cout << std::endl << std::endl << std::endl;
	gen1.printPopulation();

	//gen2 = gen1.generateNewGeneration(mapData);
	//std::cout << std::endl << std::endl << std::endl;
	//gen2.printPopulation();

	//gen3 = gen2.generateNewGeneration(mapData);
	//std::cout << std::endl << std::endl << std::endl;
	//gen3.printPopulation();

	//gen4 = gen3.generateNewGeneration(mapData);
	//std::cout << std::endl << std::endl << std::endl;
	//gen4.printPopulation();

	//gen5 = gen4.generateNewGeneration(mapData);
	//std::cout << std::endl << std::endl << std::endl;
	//gen5.printPopulation();

	//gen6 = gen5.generateNewGeneration(mapData);
	//std::cout << std::endl << std::endl << std::endl;
	//gen6.printPopulation();

	//gen7 = gen6.generateNewGeneration(mapData);
	//std::cout << std::endl << std::endl << std::endl;
	//gen7.printPopulation();

	//gen8 = gen7.generateNewGeneration(mapData);
	//std::cout << std::endl << std::endl << std::endl;
	//gen8.printPopulation();

	//gen9 = gen8.generateNewGeneration(mapData);
	//std::cout << std::endl << std::endl << std::endl;
	//gen9.printPopulation();


	std::cin.get();
	std::cin.get();



	return 0;
}