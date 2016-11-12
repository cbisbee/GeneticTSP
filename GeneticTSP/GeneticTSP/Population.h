#pragma once
#include <vector>
#include <algorithm>
#include "Chromosome.h"

//This class represents a population of chrosomes

class Population {
private:
	std::vector<Chromosome> chromosomes;
	double maxFitness = 0.0;
	double minFitness = 0.0;
	double avgFitness = 0.0;
	int generationNumber;
	//Chromosome chromosomes[TOURSIZE];
public:
	Population(int _generationNumber) {
		generationNumber = _generationNumber;
		chromosomes.reserve(TOURSIZE);
		chromosomes.resize(TOURSIZE);
	}
	Population() {
		chromosomes.reserve(TOURSIZE);
		chromosomes.resize(TOURSIZE);
	}
	void InitializePopulation(std::map<int, City> mapData) {
		for (int i = 0; i < TOURSIZE; i++) {
			Chromosome newChrom;
			newChrom.initializeChromsome(mapData);
			chromosomes[i] = newChrom;
		}
		sortPopulationByFitness();
		setAvgFitness();
		setMaxFitness();
		setMinFitness();
	}
	void sortPopulationByFitness() {
		std::sort(chromosomes.begin(), chromosomes.end());
	}
	void printPopulation() {
		std::cout << "Generation " << generationNumber << ":" << std::endl;
		for (int i = 0; i < chromosomes.size(); i++)
			chromosomes[i].printChromosome();

		std::cout << std::endl;
		std::cout << "Generation min fitness: " << minFitness << std::endl;
		std::cout << "Generation max fitness: " << maxFitness << std::endl;
		std::cout << "Generation avg fitness: " << avgFitness << std::endl;
	}
	void setMinFitness() {
		double currentMin = chromosomes[0].getFitness();
		for (int i = 1; i < chromosomes.size(); i++) {
			if (chromosomes[i].getFitness() < currentMin)
				currentMin = chromosomes[i].getFitness();
		}
		minFitness = currentMin;
	}
	void setMaxFitness() {
		double currentMax = chromosomes[0].getFitness();
		for (int i = 1; i < chromosomes.size(); i++) {
			if (chromosomes[i].getFitness() > currentMax)
				currentMax = chromosomes[i].getFitness();
		}
		maxFitness = currentMax;
	}
	void setAvgFitness() {
		double sum = 0.0;
		for (int i = 0; i < chromosomes.size(); i++) {
			sum += chromosomes[i].getFitness();
		}
		avgFitness = (sum / chromosomes.size());
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