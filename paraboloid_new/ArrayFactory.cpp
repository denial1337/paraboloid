#include "ArrayFactory.h"

double * ArrayFactory::create_1d_zeros_array(int size)
{
	double * array = new double[size];
	for (int i(0); i < size; i++)
		array[i] = 0;
	return array;
}

double ** ArrayFactory::create_2d_zeros_array(int row, int column)
{
	double ** array = new double*[row];
	for (int i(0); i < row; i++)
		array[i] = new double[column];
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
			array[i][j] = 0;
	return array;
}

void ArrayFactory::delete_1d_array(double * array)
{
	delete[] array;
}

void ArrayFactory::delete_2d_array(double ** array, int size)
{
	for (int i(0); i < size; i++)
		delete[] array[i];
	delete[] array;
}

void ArrayFactory::output_1d_array(double * array, int size)
{
	std::cout << std::endl << "begin" << std::endl;
	for (int i = 0; i < size; i++)
		std::cout << array[i] << '\n';
	std::cout << "end\n";
}

void ArrayFactory::output_2d_array(double ** array, int row, int column)
{
	std::cout << std::endl << "begin" << std::endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
			std::cout << array[i][j] << '\t';
		std::cout << std::endl;
	}
	std::cout << "end\n";
}

void ArrayFactory::delete_1d_array(int * array)
{
	delete[] array;
}

void ArrayFactory::delete_2d_array(int ** array, int size)
{
	for (int i(0); i < size; i++)
		delete[] array[i];
	delete[] array;
}

void ArrayFactory::output_1d_array(int * array, int size)
{
	std::cout << std::endl << "begin" << std::endl;
	for (int i = 0; i < size; i++)
		std::cout << array[i] << '\n';
	std::cout << "end\n";
}

void ArrayFactory::output_2d_array(int ** array, int row, int column)
{
	std::cout << std::endl << "begin" << std::endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
			std::cout << array[i][j] << '\t';
		std::cout << std::endl;
	}
	std::cout << "end\n";
}