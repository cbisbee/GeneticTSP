#pragma once
#include <vector>
#include <algorithm>
#include "Chromosome.h"

//This class represents a population of chrosomes

class Population {
private:
	std::vector<Chromosome> chromosomes;

public:
	Population(int length) {
		chromosomes.reserve(length);
	}
	void InitializePopulation() {
		for (int i = 0; i < chromosomes.size(); i++) {
			Chromosome newChrom = Chromosome();
			newChrom.initializeChromsome();
			chromosomes[i] = newChrom;
		}
		sortPopulationByFitness();
	}
	void sortPopulationByFitness() {
		std::sort(chromosomes.begin(), chromosomes.end());
	}



};