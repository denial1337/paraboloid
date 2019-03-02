#pragma once

class Node
{
private:
	double ** nodes;
	int rows;
	int columns;
	int * limits;
public:
	Node(int * s, int _columns);
	~Node();
	double ** get_nodes() { return this->nodes; }
	int get_rows() { return this->rows; }
	int get_columns() { return this->columns; }
	int * get_limits() { return this->limits; }
	int node_coordinate_number(int * limits);
	void set_nodes(double * params, int * s, double * h);//остается нерешенным вопрос - сколько циклов будет при 5 параметрах(без фокуса, например)
	void set_limits(int * s, int node_columns);
};

