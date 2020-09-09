/*************************************************************************
	> File Name: 129.n个数的最小数.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Mon 11 May 2020 10:37:37 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
	int n, x;
	cin >> n;
	int min = 10000;
	for (int i = 0; i < n; i++) {
		cin >> x;
		min = min > x ? x : min;
	}
	cout << min << endl;
	return 0;
}
