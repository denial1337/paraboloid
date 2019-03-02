#include "DataManager.h"
#include <iostream>
#include <fstream>


DataManager::~DataManager()
{
	for (int i = 0; i < size; i++)
		delete[] data[i];
	for (int i = 0; i < size; i++)
		delete[] extremums[i];
}

void DataManager::read_data(std::string filename)
{
	std::ifstream fin(filename);
	int filesize = 0;				//переменная для подсчета количества точек

									/*подсчет количества точек в файле*/
	if (!(fin.is_open()))
	{
		std::cout << "Ошибка при чтении файла\n";
		getchar();
	}
	else
	{
		char tch[1024];								//переменная для считывания
		while (!fin.eof())
		{
			fin.getline(tch, 1024);
			if (tch[0] != '\0' && tch[0] != '\n')	//если в начале строки не встречен переход на новую строчку или символ конца строки инкрементируем счетчик
				filesize++;
		}
	}
	fin.close();
	fin.open(filename);
	double ** data = new double*[filesize];			//массив точек
	for (int k(0); k < filesize; k++)
		data[k] = new double[3];
	if (fin.eof())
		fin.clear();
	int cnt = 0;
	if (!(fin.is_open()))
	{
		std::cout << "Ошибка при чтении файла\n";
		getchar();
	}
	else
	{
		while (!fin.eof())
		{
			fin >> data[cnt][0];
			fin >> data[cnt][1];
			fin >> data[cnt][2];
			cnt++;
		}
	}
	fin.close();

	while (data[filesize - 1][0] == 0 && data[filesize - 1][0] == 0 && data[filesize - 1][0] == 0)
		filesize--;
	std::cout<< "filesize " << filesize << std::endl;
	this->data = data;
	this->set_size(filesize);
}

void DataManager::output_data()
{
	if(size)
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < 3; j++)
			std::cout << data[i][j] << '\t';
		std::cout << std::endl;
	}
}

void DataManager::set_extremums()
{
	/*находим максимумы и минимумы*/
	double ** data = this->get_data();
	double ** result = new double*[6];
	for (int i = 0; i < 3; i++)
		result[i] = new double[2]{ data[0][i], data[0][i] };

	for (int j = 0; j < this->get_size(); j++)
	{
		if (data[j][0] < result[0][0]) result[0][0] = data[j][0];
		if (data[j][0] > result[0][1]) result[0][1] = data[j][0];
		if (data[j][1] < result[1][0]) result[1][0] = data[j][1];
		if (data[j][1] > result[1][1]) result[1][1] = data[j][1];
		if (data[j][2] < result[2][0]) result[2][0] = data[j][2];
		if (data[j][2] > result[2][1]) result[2][1] = data[j][2];
	}
	this->extremums = result;
}