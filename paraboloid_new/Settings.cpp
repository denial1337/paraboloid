#include "Settings.h"


Settings::Settings()
{
	int val = 4;
	s = new int[6]{ val, val, val, val, val, val };  	/*������ ������������� ���������� �������� ������*/
	m = 4;												/*��������� ���������*/
	n = 6;												/*���������� ������ �����������*/
	filename = "�����������.dat";
}

