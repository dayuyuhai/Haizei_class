/*************************************************************************
	> File Name: 56.第N组排列.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 02 Jun 2020 06:06:07 PM CST
 ************************************************************************/

#include<iostream>
#include<string.h>
using namespace std;
#define max_n 10

int num[10];
int fac[10];

void init() {
	fac[0] = 1;
	num[0] = 1;
	for (int i = 1; i < 10; i++) {
		fac[i] = i * fac[i - 1];
		num[i] = 1;
	}
	return;
}

int get_num(int k, int val, int &x) {
	int step = k / val;
	for (int t = 0; t <= step; x += (t <= step)) {
		t += num[x];
	}
	num[x] = 0;
	k %= val;
	return k;
}

int main() {
	int x, y;
	init();
	cin >> x >> y;
	y--;
	for (int i = x - 1; i >= 0; i--) {
		int b = 1;
		y = get_num(y, fac[i], b);
		cout << b;
	}
	cout << endl;

	return 0;
}
