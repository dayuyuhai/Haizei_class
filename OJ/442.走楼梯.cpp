/*************************************************************************
	> File Name: 442.走楼梯.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Wed 13 May 2020 11:53:18 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int pa(int n) {
	if (n == 1) return 1;
	if (n == 2) return 2;
	return pa(n - 1) + pa(n - 2);
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		!(i == 1) && cout << ' ';
		cout << pa(i);
	}
	return 0;
}
