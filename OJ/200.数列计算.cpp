/*************************************************************************
	> File Name: 200.数列计算.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 10:29:51 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	double sum = 0;
	int a = 4, b = 7, t;
	while (n--) {
		sum += 1.0 * a / b;
		if (n > 0) {
			t = a;
			a = b;
			b = t + b;
		}
	}
	cout << a << '/' << b << endl;
	printf("%.2lf", sum);

	return 0;
}
