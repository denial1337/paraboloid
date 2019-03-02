#pragma once
#include <iostream>
class ArrayFactory
{
public:
	ArrayFactory() {}
	~ArrayFactory() {}

	double * create_1d_zeros_array(int size);
	double ** create_2d_zeros_array(int row, int column);
	void delete_1d_array(double * array);
	void delete_2d_array(double ** array, int size);
	void output_1d_array(double * array, int size);
	void output_2d_array(double ** array, int row, int column);
	void delete_1d_array(int * array);
	void delete_2d_array(int ** array, int size);
	void output_1d_array(int * array, int size);
	void output_2d_array(int ** array, int row, int column);
private:

};

