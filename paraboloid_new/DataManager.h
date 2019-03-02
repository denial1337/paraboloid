#pragma once
#include <string>
class DataManager
{
private:
	int size;
	double ** data;
	double ** extremums; //хранит минимумы и максимумы по осям в виде [[xmin,xmax],[ymin,ymax],[zmin,zmax]]
public:
	DataManager() {}
	~DataManager();

	void read_data(std::string filename);
	void set_size(int _size) { size = _size; }
	int get_size() { return this->size; }
	double ** get_data() { return this->data; }
	void output_data(); 
	void set_extremums();
	double ** get_extremums() { return this->extremums; }

};

