#include "functions.h"
#include <iostream>
#include <fstream>
#include <exception>

using namespace std;

double * affine_center(double ** data, int filesize)
{
	double * arr = new double[3];
	for (int k(0); k < filesize; k++)
	{
		arr[0] += data[k][0];
		arr[1] += data[k][1];
		arr[2] += data[k][2];
	}
	arr[0] /= filesize;
	arr[1] /= filesize;
	arr[2] /= filesize;
	return arr;
}


double target_func(double ** data, double * a, int data_size)
{
	double result = 0;
	for (int i = 0; i < data_size; i++)
		result += parab(a, data[i]);
	return result; 
}


double parab(double * a, double * data)
{
	return pow(rho(a, data) -
		pow(v1(a)*(data[0] - (a[0] - 2 * a[5] * v1(a))) + v2(a)*(data[1] - (a[1] - 2 * a[5] * v2(a))) + v3(a)*(data[2] - (a[2] - 2 * a[5] * v3(a))), 2), 2);
}


double * V(double * a)
{
	return new double[3]{
		(1 - a[3] * a[3]) / (1 + a[3] * a[3])*(1 - a[4] * a[4]) / (1 + a[4] * a[4]),
		2 * a[3] / (1 + a[3] * a[3])*(1 - a[4] * a[4]) / (1 + a[4] * a[4]),
		2 * a[4] / (1 + a[4] * a[4])
	};
}


double * Ver(double * a, double * v)
{
	return new double[3]{ 
		a[0] - v[0] * a[5],
		a[1] - v[1] * a[5],
		a[2] - v[2] * a[5],
	};
}

double * TT(double * a, double * v)
{
	return new double[3]{
		a[0] - 2 * a[5] * v[0],
		a[1] - 2 * a[5] * v[1],
		a[2] - 2 * a[5] * v[2]
	};
}


double DIR(double * a, double * v, double * tt, double * data)
{
	static double tmp = v[0] * (data[0] - tt[0]) + v[1] * (data[1] - tt[1]) + v[2] * (data[2] - tt[2]);
	delete[] v;
	delete[] tt;
	return tmp;
}


double rho(double * a, double * data)
{
	return (data[0] - a[0])*(data[0] - a[0]) +
		(data[1] - a[1])*(data[1] - a[1]) +
		(data[2] - a[2])*(data[2] - a[2]);

}


int counter(int * m)
{
	return m[0] +
		m[1] * (m[0] + 1) +
		m[2] * (m[0] + 1)*(m[1] + 1) +
		m[3] * (m[0] + 1)*(m[1] + 1) * (m[2] + 1) +
		m[4] * (m[0] + 1)*(m[1] + 1) * (m[2] + 1) * (m[3] + 1) +
		m[5] * (m[0] + 1)*(m[1] + 1) * (m[2] + 1) * (m[3] + 1) * (m[4] + 1);
}

double def_f0(double ** e)
{
	double ax, ay, az;
	ax = (e[0][1] - e[0][0]) / 2;
	ay = (e[1][1] - e[1][0]) / 2;
	az = (e[2][1] - e[2][0]) / 2;
	double f0 = sqrt(ax*ax + ay*ay + az*az)*0.9;
	return f0;
}

double * step_delimiter(double ** e, int m)
{
	double * result = new double[3]{
		(e[0][1] - e[0][0]) / m,
		(e[1][1] - e[1][0]) / m,
		(e[2][1] - e[2][0]) / m
	};
	return result;
}


double * sphere_center(double a, double * center, double * v)
{
	double * res = new double[3];
	for (int i(0); i < 3; i++)
		res[i] = center[i] + a*v[i];
	return res;
}


double sphere(double * afc, double * v, double * vv, double ** mt, double a, int filesize, int mtsize)
{
	double * sc = sphere_center(a, afc, v);
	double res = 0;
	for (int i(0); i < mtsize; i++)
	{
		res += ((mt[i][0] - sc[0])*(mt[i][0] - sc[0])
			+ (mt[i][1] - sc[1])*(mt[i][1] - sc[1])
			+ (mt[i][2] - sc[2])*(mt[i][2] - sc[2]) - a*a)*
			((mt[i][0] - sc[0])*(mt[i][0] - sc[0])
				+ (mt[i][1] - sc[1])*(mt[i][1] - sc[1])
				+ (mt[i][2] - sc[2])*(mt[i][2] - sc[2]) - a*a)*vv[i];
	}
	return res;
}

void def_vector_direction(double * afc, double * v, double * vv, double ** mt, double a, int filesize, int mtsize)
{
	if(sphere(afc, v, vv, mt, a, filesize, mtsize) > sphere(afc, v, vv, mt, -a, filesize, mtsize))
		for (int i = 0; i < 3; i++)
			v[i] *= -1;
}

double * def_focus(double * ac, double * v, double F0)
{
	double * focus = new double[3];
	for (int i = 0; i < 3; i++)
		focus[i] = ac[i] + F0*v[i];
	return focus;
}

double def_mn(double * roots)
{
	double mn = 0; //êîðåíü ñóììû êâàäðàòîâ êîðíåé
	for (int i(0); i < 3; i++)
		mn += roots[i] * roots[i];
	return sqrt(mn);
}


double * minimize(Net & net, Node & node)
{
	double * func_val = new double[node.get_rows()];
	double min_func_val = target_func(net.get_net(), node.get_nodes()[0], net.get_net_size());
	int min_func_val_num = 0;
	for (int i = 1; i < node.get_rows(); i++)
	{
		func_val[i] = target_func(net.get_net(), node.get_nodes()[i], net.get_net_size());
		if (func_val[i] < min_func_val)
		{
			min_func_val = func_val[i];
			min_func_val_num = i;
		}
	}
	delete[] func_val;
	return node.get_nodes()[min_func_val_num];
}

double * minimize_main(Net & net, Node & node, Settings & settings, double * h, double * params)
{
	int * s = settings.get_s();
	for (int i = 0; i < settings.get_n(); i++)
	{
		node.set_nodes(params, s, h);
		params = minimize(net, node);
		h[0] = h[0] / s[0]; h[1] = h[1] / s[1]; h[2] = h[2] / s[2];
		h[3] = h[3] / s[3]; h[4] = h[4] / s[4]; h[5] = h[5] / s[5];
	}
	return params;
}

void output_result(double * params, Net & net)
{
	cout << "ÐÅÇÓËÜÒÀÒ ÌÈÍÈÌÈÇÀÖÈÈ\n";
	cout << params[0] << '\t' << params[1] << '\t' << params[2] <<
		'\t' << params[3] << '\t' << params[4] << '\t' << params[5] << '\n';
	cout << "ÌÈÍÈÌÀËÜÍÎÅ ÇÍÀ×ÅÍÈÅ ÔÓÍÊÖÈÈ\n";
	cout << target_func(net.get_net(), params, net.get_net_size()) << endl;
	cout << "ÔÎÊÓÑ\n" << params[0] << '\t' << params[1] << '\t' << params[2] << '\n';
	double * v = V(params);
	double * ver = Ver(params, v);
	double * tt = TT(params, v);
	cout << "ÍÀÏÐÀÂËßÞÙÈÉ ÂÅÊÒÎÐ ÎÑÈ\n" << v[0] << '\t' << v[1] << '\t' << v[2] << '\n';
	cout << "ÂÅÐØÈÍÀ\n" << ver[0] << '\t' << ver[1] << '\t' << ver[2] << '\n';
	cout << "ÒÎ×ÊÀ, ×ÅÐÅÇ ÊÎÒÎÐÓÞ ÏÐÎÕÎÄÈÒ ÄÈÐÅÊÒÎÐÈÀËÜÍÀß ÏËÎÑÊÎÑÒÜ\n" << tt[0] << '\t' << tt[1] << '\t' << tt[2] << '\n';
	delete[] v;
	delete[] ver;
	delete[] tt;
}


