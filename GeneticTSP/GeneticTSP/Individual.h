#pragma once
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iomanip>
#include "City.h"

const int TOURSIZE = 25; //24 cities plus return city

//This class represents a "chromosome" in our populaiton
//an chromosome, in this case, represents a trip
class Individual{
private:
	std::vector<int> visitedCities;
	double costOfTrip;
	int numUniqueCitiesVisited;
	bool fullTour; //start and stop in same place
	bool travelingSalesman;
	double fitness;
	double probability;
	double relativeFitness;
public:
	Individual() {
		visitedCities.reserve(TOURSIZE);
		visitedCities.resize(TOURSIZE);
		costOfTrip = -1;
		numUniqueCitiesVisited = -1;
		fullTour = false;
		fitness = -1;
		for (int i = 0; i < TOURSIZE; i++)
			visitedCities[i] = -1;
	}
	Individual(std::vector<int> &_visitedCities) {
		visitedCities = _visitedCities;
		costOfTrip = -1;
		numUniqueCitiesVisited = -1;
		fullTour = false;
		fitness = -1;
	}
	std::vector<int> getVisitedCities() {
		return visitedCities;
	}
	int getNumUniqueCitiesVisited() {
		return numUniqueCitiesVisited;
	}
	bool getFullTour() {
		return fullTour;
	}
	double getFitness() {
		return fitness;
	}
	double getCostOfTrip() {
		return costOfTrip;
	}
	bool getTravelingSalesman() {
		return travelingSalesman;
	}
	//This function shuffles the list of visited cities
	void mutate() {
		int temp;
		for (int i = 0; i < visitedCities.size(); i++) {
			if ((i + 3) < visitedCities.size()) {
				temp = visitedCities[i];
				visitedCities[i] = visitedCities[i + 3];
				visitedCities[i + 3] = temp;
			}
			else {
				temp = visitedCities[i];
				visitedCities[i] = visitedCities[i - 1];
				visitedCities[i - 1] = temp;
			}
		}
	}
	void setNumUniqueCitiesVisited() {
		numUniqueCitiesVisited = 0;
		std::vector<int> cityList;
		bool inList = false;
		for(int i = 0; i < visitedCities.size(); i++) {
			for(int j = 0; j < cityList.size(); j++) {
				if (visitedCities[i] == cityList[j]) {
					inList = true;
				}
			}
			if (!inList) {
				cityList.push_back(visitedCities[i]);
				numUniqueCitiesVisited += 1;
			}
		}
	}
	void setFullTour() {
		if (visitedCities[0] == visitedCities[visitedCities.size() - 1]) fullTour = true;
		else
			fullTour = false;
	}
	void setFitness(std::map<int, City> mapData) {
		setFullTour();
		setNumUniqueCitiesVisited();
		setCostOfTrip(mapData);
		fitness = 0;
		if (fullTour)
			fitness += 100.0;
		else
			fitness += 50.0;
		fitness += numUniqueCitiesVisited *3.5;
		fitness -= costOfTrip * .2;
	}
	void setCostOfTrip(std::map<int,City> mapData) {
		City curCity = City();
		City nextCity = City();
		double curCost = 0;
		costOfTrip = 0;
		for (int i = 0; i < visitedCities.size() - 2; i++) {
			curCity.setAll(visitedCities[i], mapData[visitedCities[i]].getXCor(), mapData[visitedCities[i]].getYCor());
			nextCity.setAll(visitedCities[i + 1], mapData[visitedCities[i + 1]].getXCor(), mapData[visitedCities[i + 1]].getYCor());
			curCost = curCity.calculateDistance(nextCity);
			costOfTrip += curCost;
		}
	}
	void setTravelingSalesman() {
		if (numUniqueCitiesVisited == TOURSIZE && fullTour)
			travelingSalesman = true;
		else
			travelingSalesman = false;
	}
	void initializeIndividual(std::map<int, City> mapData) {
		int i = 0;
		while (i < TOURSIZE)
		{
			int city = rand() % TOURSIZE;
			if (!containsCity(city))
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
		std::cout << std::left << std::setw(10) << "fitness" << fitness;
		std::cout << std::endl;
	}
	void addCity(int city) {
		visitedCities.push_back(city);
	}
	int getCity(int index) {
		return visitedCities[index];
	}
	void setProbability(double _probability) {
		probability = _probability;
	}
	double getProbability() {
		return probability;
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
	bool containsCity(int city)
	{
		for (int i = 0; i < TOURSIZE; i++)
		{
			if (visitedCities.at(i) == city)
				return true;
		}
		return false;
	}
	void setRelativeFitness(double _relativeFitness)
	{
		relativeFitness = _relativeFitness;
	}

	double getRelativeFitness()
	{
		return relativeFitness;
	}
};