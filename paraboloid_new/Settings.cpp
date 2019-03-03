#include "Settings.h"


Settings::Settings()
{
	int val = 4;
	s = new int[6]{ val, val, val, val, val, val };  	/*вектор коэффициентов уменьшения размеров клетки*/
	m = 4;												/*основание разбиения*/
	n = 6;												/*количество циклов минимизации*/
	filename = "НЕСМЕЩЕННЫЙ.dat";
}

