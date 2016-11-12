#pragma once
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <map>
#include <iomanip>
#include "City.h"

const int TOURSIZE = 25; //24 cities plus return city

//This class represents an "chromosome" in our populaiton
//an chromosome, in this case, represents a trip
class Chromosome{
private:
	std::vector<int> visitedCities;
	double costOfTrip;
	int numUniqueCitiesVisited;
	bool fullTour; //start and stop in same place
	double fitness;
public:
	Chromosome() {
		visitedCities.reserve(TOURSIZE);
		costOfTrip = -1;
		numUniqueCitiesVisited = -1;
		fullTour = false;
		fitness = -1;
	}
	Chromosome(std::vector<int> &_visitedCities) {
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
	void mutate(); //TODO: Figure out mutation logic for this function
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
	void initializeChromsome(std::map<int, City> mapData) {
		visitedCities.clear();
		for (int i = 0; i < TOURSIZE; i++) {
			int city = rand() % TOURSIZE;
			visitedCities.push_back(city);
		}
		setFitness(mapData);
	}
	void printChromosome() {
		for (int i = 0; i < visitedCities.size(); i++) {
			std::cout << std::left << std::setw(4) << visitedCities[i];
		}
		std::cout << std::left << std::setw(10) << "fitness" << fitness;
		std::cout << std::endl;
	}
	bool operator<(const Chromosome& B) {
		return (this->fitness < B.fitness);
	}
};