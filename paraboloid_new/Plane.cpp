#include "Plane.h"



Plane::Plane(DataManager & dm)
{
	this->row = 3;
	this->column = 4;
	this->set_coefficients(dm);
}

Plane::~Plane()
{
	for (int i = 0; i < this->row; i++)
		delete[] coefficients[i];
}

void Plane::set_coefficients(DataManager & dm)
{
	int rows_ = this->row;
	int columns_ = this->column;
	double ** parametres = new double*[rows_];
	/*для суммирования инициализируем нулями*/
	for (int j(0); j < rows_; j++)
	{
		parametres[j] = new double[columns_];
		for (int k(0); k < columns_; k++)
			parametres[j][k] = 0;
	}
	for (int i(0); i < dm.get_size(); i++)
		for (int j(0); j < rows_; j++)
		{
			for (int k(0); k < columns_ - 1; k++) //проходим цикл до 3 т.к. 4ый элемент суммируем отдельно
				parametres[j][k] += dm.get_data()[i][j] * dm.get_data()[i][k];
			parametres[j][3] += dm.get_data()[i][j];
		}
	for (int j(0); j < rows_; j++)
		for (int k(0); k < columns_; k++)
			parametres[j][k] /= dm.get_size();
	for (int j(0); j < rows_; j++) //домножаем на -1
		parametres[j][3] *= -1;
	this->coefficients = parametres;
}
