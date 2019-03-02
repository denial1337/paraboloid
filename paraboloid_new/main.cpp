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
	std::cout << "��������� ��������.\n";
	ArrayFactory af;
	DataManager dm;
	Settings settings;
	/*������ ������ �� �����*/
	dm.read_data(settings.get_filename());
	/*������� ��������� � �������� �� ������� ����������*/
	dm.set_extremums();
	double ** data = dm.get_data();
	int filesize = dm.get_size();
	/*���� ������� �����*/
	double * ac = af.create_1d_zeros_array(3);
	aff_center(data, ac, filesize);
	/*������ ������ ���������� ���������*/
	double ** extremum = dm.get_extremums();
	double F0 = find_f0(extremum);
	/*���� ��������� �� �����*/
	double * step = step_delimiter(extremum, settings.get_m());
	/*���� ���������� ��������*/
	Net net(dm, extremum, step, settings.get_m());
	/*���������� ���������*/
	Plane plane(dm);
	double * roots = gaus_run(plane.get_coefficients());
	double mn = def_mn(roots);
	double v[3] = { roots[0] / mn,roots[1] / mn,roots[2] / mn };
	def_vector_direction(ac, v, net.get_weight_list(), net.get_net(), F0, filesize, net.get_net_size());
	/*������ ������ ������*/
	double * focus = def_focus(ac, v, F0);
	/*������ ������ ��������� �������� ����������*/
	double * params = new double[6]{ focus[0], focus[1], focus[2], 0.0, 0.0, F0 };
	/*������ ������ ������� ������������ ������ ��������������� �������*/
	double * h = new double[6]{
		F0, F0, F0, 1.0, 1.0, F0 / 3 };
	int * s = settings.get_s();
	int node_columns = 6;
	Node node(s, node_columns);
	params = minimize_main(net, node, settings, h, params);
	cout << "��������� �����������\n";
	cout << params[0] << '\t' << params[1] << '\t' << params[2] <<
		'\t' << params[3] << '\t' << params[4] << '\t' << params[5] << '\n';
	cout << "����������� �������� �������\n";
	cout << target_func(net.get_net(), params, net.get_net_size()) << endl;
	output_result(params);

	af.delete_1d_array(roots);
	af.delete_1d_array(focus);
	af.delete_1d_array(params);
	af.delete_1d_array(s);
	af.delete_1d_array(h);
	af.delete_1d_array(ac);

	getchar();
	return 0;
}


