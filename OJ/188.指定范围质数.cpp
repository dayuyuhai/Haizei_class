/*************************************************************************
	> File Name: 188.指定范围质数.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Wed 13 May 2020 09:03:30 AM CST
 ************************************************************************/
#include<iostream>
using namespace std;
#define max_n 1000000

int a[max_n + 5] = {0};
void init() {
	for (int i = 2; i * i <= max_n; i++) {
		if (a[i]) continue;
		for (int j = i * i; j < max_n; j += i) {
			a[j] = 1;
		}
	}
	return;
}

int main() {
	int n, m;
	cin >> n >> m;
	init();
	for (int i = m; i <= n; i++) {
		a[i] == 0 && cout << i << endl;
	}
	return 0;
}


