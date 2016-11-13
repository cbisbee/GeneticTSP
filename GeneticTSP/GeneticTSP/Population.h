#pragma once
#include <vector>
#include <algorithm>
#include "Individual.h"

//This class represents a population of chrosomes

class Population {
private:
	std::vector<Individual> individuals;
	double maxFitness = 0.0;
	double minFitness = 0.0;
	double avgFitness = 0.0;
	int generationNumber;
public:
	Population(int _generationNumber) {
		generationNumber = _generationNumber;
		individuals.reserve(TOURSIZE);
		individuals.resize(TOURSIZE);
	}
	Population() {
		individuals.reserve(TOURSIZE);
		individuals.resize(TOURSIZE);
	}
	void InitializePopulation(std::map<int, City> mapData) {
		for (int i = 0; i < TOURSIZE; i++) {
			Individual newInd;
			newInd.initializeIndividual(mapData);
			individuals[i] = newInd;
		}
		sortPopulationByFitness();
		setAvgFitness();
		setMaxFitness();
		setMinFitness();
	}
	void sortPopulationByFitness() {
		std::sort(individuals.begin(), individuals.end());
	}
	void printPopulation() {
		std::cout << "Generation " << generationNumber << ":" << std::endl;
		for (int i = 0; i < individuals.size(); i++)
			individuals[i].printIndividual();

		std::cout << std::endl;
		std::cout << "Generation min fitness: " << minFitness << std::endl;
		std::cout << "Generation max fitness: " << maxFitness << std::endl;
		std::cout << "Generation avg fitness: " << avgFitness << std::endl;
	}
	void setMinFitness() {
		double currentMin = individuals[0].getFitness();
		for (int i = 1; i < individuals.size(); i++) {
			if (individuals[i].getFitness() < currentMin)
				currentMin = individuals[i].getFitness();
		}
		minFitness = currentMin;
	}
	void setMaxFitness() {
		double currentMax = individuals[0].getFitness();
		for (int i = 1; i < individuals.size(); i++) {
			if (individuals[i].getFitness() > currentMax)
				currentMax = individuals[i].getFitness();
		}
		maxFitness = currentMax;
	}
	void setAvgFitness() {
		double sum = 0.0;
		for (int i = 0; i < individuals.size(); i++) {
			sum += individuals[i].getFitness();
		}
		avgFitness = (sum / individuals.size());
	}
	void setGenerationNumber(int generation) {
		generationNumber = generation;
	}
	double getMinFitness() {
		return minFitness;
	}
	double getMaxFitness() {
		return maxFitness;
	}
	double getAvgFitness() {
		return avgFitness;
	}
	int getGenerationNumber() {
		return generationNumber;
	}
};