#pragma once
#include <math.h>

//This class represents a gene in the chromosome

class City
{
private:
	int name;
	int xCor;
	int yCor;
public:
	City() {
		name = -1;
		xCor = -1;
		yCor = -1;
	}
	City(int _name, int x, int y) {
		name = _name;
		xCor = x;
		yCor = y;
	}
	int getName() {
		return name;
	}
	int getXCor() {
		return xCor;
	}
	int getYCor() {
		return yCor;
	}
	float calculateDistance(City cityB) {
		return std::sqrt((std::pow(xCor - cityB.getXCor, 2) + std::pow(yCor - cityB.getYCor(), 2)));
	}
};