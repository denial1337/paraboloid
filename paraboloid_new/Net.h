#pragma once
#include "DataManager.h"

class Net
{
private:
	double * node_numbers;  //количество точек в узле
	double ** net;			//узлы сети
	int net_size;			//количество точек
	double * weight_list;   //список весов
public:
	Net(DataManager & dm, double ** extremum, double * step, int m);
	~Net();
	int numer(int n, int i, int j, int k); //нумерация сети, конвертация из трёхмерных координат в одномерные
	double ** get_net() { return net; }
	double * get_node_numbers() { return node_numbers; }
	int get_net_size() { return net_size; }
	double * get_weight_list() { return weight_list; }
};

