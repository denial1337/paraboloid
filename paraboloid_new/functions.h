#pragma once
#include <string>
#include "DataManager.h"
#include "Net.h"
#include "Node.h"
#include "Settings.h"
#include "ArrayFactory.h"


using namespace std;

void aff_center(double ** data, double * arr, int filesize);
double paraboloid(double * a, double * data);
double target_func(double ** data, double * a, int data_size);
double * V(double * a);
double * Ver(double * a, double * v);
double * TT(double * a, double * v);
double DIR(double * a, double * v, double * tt, double * data);
double rho(double * a, double * data);
int counter(int * m);
double find_f0(double ** extremums);
double * step_delimiter(double ** extremums, int m);
double sphere(double * afc, double * v, double * vv, double ** mt, double a, int filesize, int mtsize);
double * sphere_center(double a, double * center, double * v);
void def_vector_direction(double * afc, double * v, double * vv, double ** mt, double a, int filesize, int mtsize);
double * def_focus(double * ac, double * v, double F0);
double def_mn(double * roots);

double * minimize(Net & net, Node & node);
double * minimize_main(Net & net, Node & node, Settings & settings, double * h, double * params);
void output_result(double * params);

