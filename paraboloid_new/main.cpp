#include <iostream>
#include <fstream>
#include "gaus_method.h"
#include "DataManager.h"
#include "ArrayFactory.h"
#include "functions.h"
#include "Test.h"
#include "Net.h"
#include "Node.h"
#include "Settings.h"
#include "Plane.h"

using namespace std;


int main(void)
{
	cout.setf(ios::fixed);
	cout.precision(16);
	//run_tests();getwchar();
	setlocale(LC_ALL, "RUS");
	std::cout << "Программа запущена.\n";
	ArrayFactory af;
	DataManager dm;
	Settings settings;
	/*ЧТЕНИЕ ДАННЫХ ИЗ ФАЙЛА*/
	dm.read_data(settings.get_filename());
	/*считаем максимумы и минимумы по каждомй координате*/
	dm.set_extremums();
	double ** data = dm.get_data();
	/*ищем афинный центр*/
	double * ac = affine_center(data, dm.get_size());
	/*грубая оценка фокального параметра*/
	double ** extremum = dm.get_extremums();
	double f0 = def_f0(extremum);
	/*шаги разбиения по осями*/
	double * step = step_delimiter(extremum, settings.get_m());
	/*цикл заполнения массивов*/
	Net net(dm, extremum, step, settings.get_m());
	/*нахождение плоскости*/
	Plane plane(dm);
	double * roots = gaus_run(plane.get_coefficients());
	double mn = def_mn(roots);
	double v[3] = { roots[0] / mn,roots[1] / mn,roots[2] / mn };
	def_vector_direction(ac, v, net.get_weight_list(), net.get_net(), f0, dm.get_size(), net.get_net_size());
	/*грубая оценка фокуса*/
	double * focus = def_focus(ac, v, f0);
	/*грубая оценка начальных значений параметров*/
	double * params = new double[6]{ focus[0], focus[1], focus[2], 0.0, 0.0, f0 };
	/*грубая оценка вектора полуразмеров клеток первоначального деления*/
	double * h = new double[6]{
		f0, f0, f0, 1.0, 1.0, f0 / 3 };
	int * s = settings.get_s();
	int node_columns = 6;
	Node node(s, node_columns);
	params = minimize_main(net, node, settings, h, params);

	output_result(params, net);

	af.delete_1d_array(roots);
	af.delete_1d_array(focus);
	af.delete_1d_array(params);
	af.delete_1d_array(s);
	af.delete_1d_array(h);
	af.delete_1d_array(ac);
	af.delete_2d_array(dm.get_data(), dm.get_size());

	node.~Node();
	net.~Net();
	af.~ArrayFactory();
	dm.~DataManager();
	plane.~Plane();

	getchar();
	return 0;
}


