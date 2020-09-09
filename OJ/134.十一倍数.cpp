/*************************************************************************
	> File Name: 134.十一倍数.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Mon 11 May 2020 10:42:49 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
	int a, b;
	cin >> a >> b;
	int flag = 0;
	for (int i = a; i <= b; i++) {
		if (i % 11 != 0) continue;
		(flag) && cout << ' ';
		flag = 1;
		cout << i;
	}
	return 0;
}
