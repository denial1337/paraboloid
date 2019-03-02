#pragma once
#include "DataManager.h"

class Net
{
private:
	double * node_numbers;  //���������� ����� � ����
	double ** net;			//���� ����
	int net_size;			//���������� �����
	double * weight_list;   //������ �����
public:
	Net(DataManager & dm, double ** extremum, double * step, int m);
	~Net();
	int numer(int n, int i, int j, int k); //��������� ����, ����������� �� ��������� ��������� � ����������
	double ** get_net() { return net; }
	double * get_node_numbers() { return node_numbers; }
	int get_net_size() { return net_size; }
	double * get_weight_list() { return weight_list; }
};

