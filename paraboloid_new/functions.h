#pragma once
#include <string>
#include "DataManager.h"
#include "Net.h"
#include "Node.h"
#include "Settings.h"
#include "ArrayFactory.h"
#include <math.h>


using namespace std;

double * affine_center(double ** data, int filesize);
double target_func(double ** data, double * a, int data_size);
double * V(double * a);
double * Ver(double * a, double * v);
double * TT(double * a, double * v);
double DIR(double * a, double * v, double * tt, double * data);
double rho(double * a, double * data);
int counter(int * m);
double def_f0(double ** extremums);
double * step_delimiter(double ** extremums, int m);
double sphere(double * afc, double * v, double * vv, double ** mt, double a, int filesize, int mtsize);
double * sphere_center(double a, double * center, double * v);
void def_vector_direction(double * afc, double * v, double * vv, double ** mt, double a, int filesize, int mtsize);
double * def_focus(double * ac, double * v, double F0);
double def_mn(double * roots);
double * minimize(Net & net, Node & node);
double * minimize_main(Net & net, Node & node, Settings & settings, double * h, double * params);
void output_result(double * params, Net & net);
inline double v1(double * a) {
	return (1 - a[3] * a[3]) / (1 + a[3] * a[3])*(1 - a[4] * a[4]) / (1 + a[4] * a[4]);
}

inline double v2(double * a) {
	return 2 * a[3] / (1 + a[3] * a[3])*(1 - a[4] * a[4]) / (1 + a[4] * a[4]);
}

inline double v3(double * a) {
	return 2 * a[4] / (1 + a[4] * a[4]);
}

inline double ver1(double * a, double * v, double * a5) {
	return *a - *v * *a;
}

inline double tt1(double * a, double v, double * a5) {
	return *a - 2 * *a5 * v;
}

inline double dir1(double * a, double * v, double * tt, double * data) {
	return v1(a)*(data[0] - (a[0] - 2 * a[5] * v1(a))) + v2(a)*(data[1] - (a[1] - 2 * a[5] * v2(a))) + v3(a)*(data[2] - (a[2] - 2 * a[5] * v3(a)));
}

inline double parab(double * a, double * data);
