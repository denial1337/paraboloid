#include "functions.h"
#include <iostream>
#include "Test.h"
#include "ArrayFactory.h"

using namespace std;

void run_tests()
{
	ArrayFactory af;
	double * test_V = af.create_1d_zeros_array(3);
	test_V = V(new double[6]{ 5.,3.,11.,1.,0.,1.1 });
	af.output_1d_array(test_V, 3);
	

	double * test_Ver = af.create_1d_zeros_array(3);
	test_Ver = Ver(new double[6]{ 5.,3.,11.,1.,0.,1.1 }, test_V);
	af.output_1d_array(test_Ver, 3);


	double * test_TT = af.create_1d_zeros_array(3);
	test_TT = TT(new double[6]{ 5.,3.,11.,1.,0.,1.1 }, test_V);
	af.output_1d_array(test_TT, 3);


	double test_DIR = DIR(
		new double[6]{ 5.,3.,11.,1.,0.,1.1 },
		test_V,
		test_TT,
		new double[3]{ 2., 6., 9. });
	cout << test_DIR << endl;


	double test_rho = rho(
		new double[6]{ 5.,3.,11.,1.,0.,1.1 },
		new double[3]{ 2., 6., 9. });
	cout << test_rho << endl;


	double test_paraboloid = paraboloid(
		new double[6]{ 5.,3.,11.,1.,0.,1.1 },
		new double[3]{ 2., 6., 9. });
	cout << (test_paraboloid) << endl;

	double ** test_data = af.create_2d_zeros_array(1, 3);
	test_data[0] = new double[3]{ -3.050785651, -2.517480008, 1.153588563 };
	double test_target_func = target_func(
		test_data,
		new double[6]{ -7.260683897, -.178273e-3, 9.672801767, 0., .5000000000, 6.997965761 },
		1
	);
	cout << test_target_func << endl;


	//cout << "TEST\n";
	//double * test_params = new double[6]{ 1.,1.,1.,1.,1.,1. };
	//cout << V(test_params) << endl;
	//af.output_1d_array(Ver(test_params, V(test_params)), 3);
	//af.output_1d_array(TT(test_params, V(test_params)), 3);
	//cout << DIR(test_params, V(test_params), TT(test_params, V(test_params)), net.get_net()[0]) << endl;
	//cout << paraboloid(new double[6]{ 1,1,1,1,1,1 }, net.get_net()[0]) << endl;
	//double ** test_data = new double*[1]{ net.get_net()[0] };
	//double test_target_func = target_func(test_data, new double[6]{ 1, 1, 1, 1, 1, 1 }, 1);
	//cout << test_target_func << endl;
	////af.output_1d_array(params, 6);
	//cout << target_func(net.get_net(), params, net.get_net_size()) << endl;
	//ÂÑÅ ĞÀÁÎÒÀÅÒ


	af.delete_2d_array(test_data, 1);
	af.delete_1d_array(test_Ver);
	af.delete_1d_array(test_V);
	af.delete_1d_array(test_TT);
}
