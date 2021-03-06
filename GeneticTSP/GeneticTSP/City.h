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
	void setName(int _name) {
		name = _name;
	}
	void setXCor(int _xCor) {
		xCor = _xCor;
	}
	void setYCor(int _yCor) {
		yCor = _yCor;
	}
	void setAll(int _name, int _xCor, int _yCor) {
		name = _name;
		xCor = _xCor;
		yCor = _yCor;
	}
	double calculateDistance(City cityB) {
		double deltaX = std::abs((double)(xCor - cityB.getXCor()));
		double deltaY = std::abs((double)(yCor - cityB.getYCor()));
		double deltaX2 = deltaX * deltaX;
		double deltaY2 = deltaY * deltaY;
		return std::sqrt(deltaX2 + deltaY2);
	}
};