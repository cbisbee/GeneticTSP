#pragma once
#include <vector>
#include <algorithm>
#include "Individual.h"

//This class represents a population of Individuals

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
	Population(std::vector<Individual> individualList) {
		individuals = individualList;
		sortPopulationByFitness();
		setAvgFitness();
		setMaxFitness();
		setMinFitness();
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
	void printPopulation(std::ofstream &fout) {
		fout << "Generation " << generationNumber << ":" << std::endl;
		for (int i = 0; i < individuals.size(); i++)
			individuals[i].printIndividual(fout);

		fout << std::endl;
		fout << "Generation min fitness: " << minFitness << std::endl;
		fout << "Generation max fitness: " << maxFitness << std::endl;
		fout << "Generation avg fitness: " << avgFitness << std::endl;
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
	double getTotalFitness() {
		double totalFit = 0;
		for (int i = 0; i < TOURSIZE; i++)
		{
			totalFit += individuals[i].getFitness();
		}
		return totalFit;
	}
	double getAvgFitness() {
		return avgFitness;
	}
	int getGenerationNumber() {
		return generationNumber;
	}

	Individual getIndividualAt(int pos)
	{
		if ((pos < TOURSIZE) && (pos >= 0))
			return individuals[pos];
		else
			std::cout << "Index out of bounds when getting individual from Population!" << std::endl;
	}

	void addIndividualAt(int pos, Individual newInd)
	{
		if ((pos >= 0) && (pos < TOURSIZE))
			individuals.at(pos) = newInd;
		else
			std::cout << "Index out of bound or population is full when adding individual from Populaiton!" << std::endl;
	}
	
	Individual getFittestIndividual()
	{
		Individual fittest = individuals[0];
		for (int i = 1; i < TOURSIZE; i++)
		{
			if (individuals[i].getFitness() > fittest.getFitness())
				fittest = individuals[i];
		}
		return fittest;
	}
};