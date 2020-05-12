/*************************************************************************
	> File Name: 牛顿迭代.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 12 May 2020 08:21:21 PM CST
 ************************************************************************/

#include<iostream>
#include<math.h>
using namespace std;
#define EPSL 1e-6

inline double F(double x, double n) {
	return x * x - n;
}

inline double f(double x) {
	return 2 * x;
}

double NewTon(double (*F)(double, double), double (*f)(double), double n) {
	double x1 = n / 2.0;
	while (fabs(F(x1, n)) > EPSL) {
		x1 -= F(x1, n) / f(x1);
	}
	return x1;
}

double my_sqrt(double n) {
	return NewTon(F, f, n);
}
	
int main() {
	double n;
	while (~scanf("%lf", &n)) {
		printf("%g\n", my_sqrt(n));
	}

	return 0;
}
