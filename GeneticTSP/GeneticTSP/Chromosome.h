#pragma once
#include <vector>
#include <stdlib.h>
#include <time.h>

const int TOURSIZE = 24;

//This class represents an "chromosome" in our populaiton
//an chromosome, in this case, represents a trip
class Chromosome{
private:
	std::vector<int> visitedCities;
	float costOfTrip;
	int numUniqueCitiesVisited;
	bool fullTour;
	float fitness;
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
	std::vector<int> getVisitedCities();
	int getNumUniqueCitiesVisited();
	bool getFullTour();
	float getFitness();
	float getCostOfTrip();
	void mutate();
	void setNumUniqueCitiesVisited();
	void setFullTour();
	void setFitness();
	void setCostOfTrip();
	void initializeChromsome() {
		srand(time(NULL));
		for (int i = 0; i < visitedCities.size(); i++) {
			int city = rand() % TOURSIZE + 1;
			visitedCities.push_back(city);
		}
	}
	bool operator<(const Chromosome& B) {
		return (this->fitness < B.fitness);
	}
};