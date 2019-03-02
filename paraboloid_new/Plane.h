#pragma once
#include "DataManager.h"

class Plane
{
private:
	double ** coefficients;
	int row, column;
public:
	Plane(DataManager & dm);
	~Plane();
	void set_coefficients(DataManager & dm);
	double ** get_coefficients() { return this->coefficients; }
};

