#include "Node.h"



Node::Node(int * s, int _columns)
{
	this->columns = _columns;
	set_limits(s, _columns);
	this->rows = node_coordinate_number(this->get_limits()) + 1;
}


Node::~Node()
{
	for (int i = 0; i < this->rows; i++)
		delete[] this->nodes[i];
	delete[] this->limits;
}


int Node::node_coordinate_number(int * limits)
{
	return limits[0] +
		limits[1] * (limits[0] + 1) +
		limits[2] * (limits[0] + 1)*(limits[1] + 1) +
		limits[3] * (limits[0] + 1)*(limits[1] + 1) * (limits[2] + 1) +
		limits[4] * (limits[0] + 1)*(limits[1] + 1) * (limits[2] + 1) * (limits[3] + 1) +
		limits[5] * (limits[0] + 1)*(limits[1] + 1) * (limits[2] + 1) * (limits[3] + 1) * (limits[4] + 1);
}


void Node::set_nodes(double * params, int * s, double * h)
{
	/*деление многомерного параллелепипеда(кирпича) на меньшие кирпичи
	и вычислеие координат узловых точек*/
	double params_copy[6]{ params[0], params[1], params[2], params[3], params[4], params[5] };
	if (this->nodes != nullptr)
		for (int i = 0; i < this->rows; i++)
			delete[] this->nodes[i];
	params = params_copy;
	double * l = new double[this->get_columns()];
	double * hh = new double[this->get_columns()];
	for (int i = 0; i < this->get_columns(); i++)
	{
		l[i] = params[i] - h[i];
		hh[i] = h[i] / s[i];
	}
	double ** result = new double*[this->get_rows()];
	for (int i = 0; i < this->get_rows(); i++)
		result[i] = new double[this->get_columns()];
	double * tmparray = new double[this->get_columns()];
	int * counters = new int[this->get_columns()] { 0, 0, 0, 0, 0, 0 };
	int iter_counter = 0;
	for (counters[0] = 0; counters[0] < limits[0] + 1; counters[0]++)
	{
		for (counters[1] = 0; counters[1] < limits[1] + 1; counters[1]++)
		{
			for (counters[2] = 0; counters[2] < limits[2] + 1; counters[2]++)
			{
				for (counters[3] = 0; counters[3] < limits[3] + 1; counters[3]++)
				{
					for (counters[4] = 0; counters[4] < limits[4] + 1; counters[4]++)
					{
						for (counters[5] = 0; counters[5] < limits[5] + 1; counters[5]++)
						{
							for (int i_p = 0; i_p < 6; i_p++)
								result[iter_counter][i_p] = l[i_p] + counters[i_p] * hh[i_p];
							iter_counter++;
						}
					}
				}
			}
		}
	}

	delete[] tmparray;
	delete[] counters;
	delete[] l;
	delete[] hh;

	this->nodes = result;
}


void Node::set_limits(int * s, int node_columns)
{
	int * result = new int[node_columns];
	for (int i = 0; i < node_columns; i++)
		result[i] = s[i] * 2;
	this->limits = result;
}