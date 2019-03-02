#pragma once
#include <string>

class Settings
{
private:
	int * s; 			/*������ ������������� ���������� �������� ������*/
	int m; 				/*��������� ���������*/
	int n;				/*���������� ������ �����������*/
	std::string filename;	/*������ ��� ����� � �����������*/
public:
	Settings();
	~Settings() { delete[] this->s; };
	int * get_s() { return this->s; }
	int get_m() { return this->m; }
	int get_n() { return this->n; }
	std::string get_filename() { return this->filename; }
};

