/*************************************************************************
	> File Name: 127.高利贷.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 26 May 2020 11:00:57 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

double calc(int x, int n) {
	if (n == 0) return x;
	x *= (1 + 0.06);
	calc(x, n - 1);
}
int main() {
	int x, n;
	cin >> x >> n;
	double m = x;
	for (int i = 0; i < n; i++) {
		m *= x;
	}
	cout << (int)m << endl;
	return 0;
}
