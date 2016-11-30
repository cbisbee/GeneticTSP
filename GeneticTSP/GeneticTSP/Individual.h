#pragma once
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iomanip>
#include "City.h"

const int TOURSIZE = 24; //24 cities plus return city

//This class represents a "chromosome" in our populaiton
//an chromosome, in this case, represents a trip
class Individual{
private:
	std::vector<int> visitedCities;
	double costOfTrip;
	double fitness;
	double probability;
	double relativeFitness;
public:
	Individual() {
		visitedCities.reserve(TOURSIZE);
		visitedCities.resize(TOURSIZE);
		costOfTrip = -1;
		fitness = -1;
		for (int i = 0; i < TOURSIZE; i++)
			visitedCities[i] = -1;
	}
	Individual(std::vector<int> &_visitedCities) {
		visitedCities = _visitedCities;
		costOfTrip = -1;
		fitness = -1;
	}

	double getFitness() {
		return fitness;
	}
	double getCostOfTrip() {
		return costOfTrip;
	}

	void setFitness(std::map<int, City> mapData) {
		setCostOfTrip(mapData);
		fitness = (double) (100 / (costOfTrip));
	}
	void setCostOfTrip(std::map<int,City> mapData) {
		City curCity = City();
		City nextCity = City();
		double curCost = 0;
		costOfTrip = 0;

		for (int i = 0; i < TOURSIZE; i++)
		{
			curCost = 0;
			curCity.setAll(visitedCities[i], mapData[visitedCities[i]].getXCor(), mapData[visitedCities[i]].getYCor());
			if ((i + 1) < TOURSIZE)
				nextCity.setAll(visitedCities[i + 1], mapData[visitedCities[i + 1]].getXCor(), mapData[visitedCities[i + 1]].getYCor());
			else
				nextCity.setAll(visitedCities[0], mapData[visitedCities[0]].getXCor(), mapData[visitedCities[0]].getYCor());
			curCost = curCity.calculateDistance(nextCity);
			costOfTrip += curCost;
		}

	}

	void initializeIndividual(std::map<int, City> mapData) {
		int i = 0;
		while (i < TOURSIZE)
		{
			int city = (rand() % TOURSIZE) + 1;
			if (!containsCity(city)) //CHECK THIS OUT PLEASE **************************
			{
				visitedCities.at(i) = city;
				i++;
			}
		}
		setFitness(mapData);
	}
	void printIndividual() {
		for (int i = 0; i < visitedCities.size(); i++) {
			std::cout << std::left << std::setw(4) << visitedCities[i];
		}
		std::cout << std::left << std::setw(4) << visitedCities[0];
		std::cout << std::left << std::setw(10) << "fitness" << fitness;
		std::cout << std::endl;
	}

	bool operator<(const Individual& B) {
		return (this->fitness > B.fitness);
	}
	void setCityAt(int pos, int newCity)
	{
		if (pos >= 0 && pos < TOURSIZE)
			visitedCities.at(pos) = newCity;
		else
			std::cout << "Index out of range when adding new city to Individual" << std::endl;
	}
	int getCityAt(int pos)
	{
		if (pos >= 0 && pos < TOURSIZE)
			return visitedCities.at(pos);
		else
			std::cout << "Index out of range when trying to access Individual" << std::endl;
	}
	//This function may be broken, change to use with std::find
	bool containsCity(int city)
	{
		if (std::find(visitedCities.begin(), visitedCities.end(), city) == visitedCities.end())
			return false;
		else
			return true;
	}

	//only need the next two methods for roulette wheel which I am not currently using.
	void setRelativeFitness(double _relativeFitness)
	{
		relativeFitness = _relativeFitness;
	}

	double getRelativeFitness()
	{
		return relativeFitness;
	}

	std::vector<int> getVisitedCities()
	{
		return visitedCities;
	}
};