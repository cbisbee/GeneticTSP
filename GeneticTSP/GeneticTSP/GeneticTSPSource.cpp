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

//Individual crossover()
//
//Individual reproduce(Individual indA, Individual indB, std::map<int,City> mapData)
//{
//	Individual newInd = Individual();
//	//put the first 5 of chromA into newChrom, put the second 5 of chromB into newChrom...
//	for (int i = 0; i < TOURSIZE; i++) {
//		/*
//		if ((i < 5) || (i >= 10 && i < 15) || (i >= 20))
//			newInd.addCity(indA.getCity(i));
//		else
//			newInd.addCity(indB.getCity(i));
//			*/
//		if ((i <= ((int)TOURSIZE / 2) || i == (TOURSIZE - 1)))
//			newInd.addCity(indA.getCity(i));
//		else
//			newInd.addCity(indB.getCity(i));
//	}
//	newInd.setFitness(mapData);
//	return newInd;
//}

Individual rouletteWheel(Population pop)
{

}

void mutate(Individual &curInd, std::map<int, City> mapData)
{
	//loop through individual
		//create a random number and check if it is equal to some CONSTANT MUTATION RATE
			//get a random position with the bounds of the individual
			//swap the cities at i and at the random pos you found
}

Individual crossover(Individual p1, Individual p2, std::map<int, City> mapData)
{
	//use roulette wheel or tournament selection to get p1 and p2

	int startPos = rand() % TOURSIZE; //lower bound of p1 subtour
	int endPos = rand() % TOURSIZE; //upper bound of p1 subtour

	Individual child; //creating new child

	//loop and add the subtour of p1 to child


	//loop and add the cities from p2 that aren't already in child into any remaining spots in child until that bad boy is full

	//return the new individual child

}

Population evolve(Population pop, std::map<int, City> mapData)
{
	//create new population

	//determine whether or not oyu want eletism (NEED A GLOBAL VARIABLE FOR THIS)


	//LOOP THIS UNTIL NEW POPULATION HAS TOURSIZE AMOUNT OF INDIVIDUALS
		//create two Individuals (p1 and p2) using roulette wheel or tournament selection

		//create a child Individual and set it equal to the crossover of p1 and p2

	//add a bit of mutation to each individual (this involves a loop)

	//return the new population

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

	gen1 = gen0.generateNewGeneration(mapData);
	std::cout << std::endl << std::endl << std::endl;
	gen1.printPopulation();

	gen2 = gen1.generateNewGeneration(mapData);
	std::cout << std::endl << std::endl << std::endl;
	gen2.printPopulation();

	gen3 = gen2.generateNewGeneration(mapData);
	std::cout << std::endl << std::endl << std::endl;
	gen3.printPopulation();

	gen4 = gen3.generateNewGeneration(mapData);
	std::cout << std::endl << std::endl << std::endl;
	gen4.printPopulation();

	gen5 = gen4.generateNewGeneration(mapData);
	std::cout << std::endl << std::endl << std::endl;
	gen5.printPopulation();

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