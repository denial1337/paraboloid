#include "gaus_method.h"


#include <iostream>
using namespace std;

double * gaus_run(double ** matrix)
{
	const int n = 3;
	const int m = 4;
	int i, j;
	//Метод Гаусса
	//Прямой ход, приведение к верхнетреугольному виду
	double  tmp;
	double * xx = new double[m];
	int k;

	for (i = 0; i<n; i++)
	{
		tmp = matrix[i][i];
		for (j = n; j >= i; j--)
			matrix[i][j] /= tmp;
		for (j = i + 1; j<n; j++)
		{
			tmp = matrix[j][i];
			for (k = n; k >= i; k--)
				matrix[j][k] -= tmp*matrix[i][k];
		}
	}
	/*обратный ход*/
	xx[n - 1] = matrix[n - 1][n];
	for (i = n - 2; i >= 0; i--)
	{
		xx[i] = matrix[i][n];
		for (j = i + 1; j<n; j++) 
			xx[i] -= matrix[i][j] * xx[j];
	}
	return xx;
}
