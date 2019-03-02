#include "Net.h"
#include "ArrayFactory.h"

const int COLUMN = 3;



Net::Net(DataManager & dm, double ** extremum, double * step, int m)
{
	ArrayFactory af;
	double ** data = dm.get_data();
	int tsize = m*m*m;
	this->net = af.create_2d_zeros_array(tsize, COLUMN);
	this->node_numbers = af.create_1d_zeros_array(tsize);
	int counter;
	for (int n(0); n < dm.get_size(); n++)
	{
		for (int i(0); i < m; i++)
		{
			for (int j(0); j < m; j++)
			{
				for (int k(0); k < m; k++)
				{
					if (extremum[0][0] + i*step[0] < data[n][0] && data[n][0] < extremum[0][0] + (i + 1) * step[0] &&
						extremum[1][0] + j*step[1] < data[n][1] && data[n][1] < extremum[1][0] + (j + 1) * step[1] &&
						extremum[2][0] + k*step[2] < data[n][2] && data[n][2] < extremum[2][0] + (k + 1) * step[2])
					{
						counter = numer(m, i + 1, j + 1, k + 1) - 1; //-1 для того чтобы попасть в m^3-ий номер
						net[counter][0] += data[n][0];
						net[counter][1] += data[n][1];
						net[counter][2] += data[n][2];
						node_numbers[counter]++;
					}
				}
			}
		}
	}
	for (int i(0); i < tsize; i++)
		for (int j(0); j < 3; j++)
			net[i][j] /= node_numbers[i];

	/*избавимся от нулей*/
	/*посчитаем их количество*/
	int cnt = 0;
	for (int i(0); i < tsize; i++)
		if (node_numbers[i] == 0)
			cnt++;
	/*вычтем число нулей, и запишем в массив ненулыевые*/
	int mtsize = tsize - cnt;
	double ** mt = af.create_2d_zeros_array(mtsize, 3); //new double*[mtsize];for (int j(0); j < tsize; j++) mt[j] = new double[3];	//массив без нулей
	cnt = 0;
	for (int i(0); i < tsize; i++)
		if (node_numbers[i] != 0)
		{
			for (int j(0); j < 3; j++)
				mt[cnt][j] = net[i][j];
			cnt++;
		}
	this->net = mt;
	this->net_size = mtsize;
	/*число элементарных свободных точек*/
	int num_of_points = 0;
	for (int i(0); i < tsize; i++)
		num_of_points += node_numbers[i];
	//cout << num_of_points << endl;

	/*поэлементно поделим на полученное выше число*/
	double * vv = af.create_1d_zeros_array(mtsize);
	cnt = 0; //счетчик для нового массива
	for (int i(0); i < tsize; i++)
		if (node_numbers[i] != 0)
		{
			vv[cnt] = node_numbers[i] / num_of_points;
			cnt++;
		}
	this->weight_list = vv;
}



Net::~Net()
{
}

int Net::numer(int n, int i, int j, int k)
{
	return 	i + (j - 1)*n + (k - 1)*n*n;
}
