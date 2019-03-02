#pragma once
#include <string>

class Settings
{
private:
	int * s; 			/*вектор коэффициентов уменьшения размеров клетки*/
	int m; 				/*основание разбиения*/
	int n;				/*количество циклов минимизации*/
	std::string filename;	/*полное имя файла с расширением*/
public:
	Settings();
	~Settings() { delete[] this->s; };
	int * get_s() { return this->s; }
	int get_m() { return this->m; }
	int get_n() { return this->n; }
	std::string get_filename() { return this->filename; }
};

