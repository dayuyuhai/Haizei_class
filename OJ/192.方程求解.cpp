/*************************************************************************
	> File Name: 192.方程求解.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Wed 13 May 2020 12:33:42 PM CST
 ************************************************************************/

#include<iostream>
#include<math.h>
using namespace std;
#define EPSI 1e-5
#define F(x) (x * exp(x) - a)
#define f(x) ((x + 1) * exp(x))

double NewTon(long long a) {
	double x = log(a);
	while (fabs(F(x)) > EPSI) {
		x -= (F(x) / f(x));
	}
	return x;
}

int main() {
	long long a;
	cin >> a;
	printf("%.4lf\n", NewTon(a));
	return 0;
}
