/*************************************************************************
	> File Name: 155.数列计算一.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Wed 27 May 2020 10:54:57 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
	int n;
	cin >> n;
	int t = 3;
	int k = 0;
	int sum = 0;
	for (int i = 0; i < n; i++) {
		cout << t << endl;
		sum += t;
		k += 2;
		t += k;
	}
	cout << sum << endl;
	return 0;
}
