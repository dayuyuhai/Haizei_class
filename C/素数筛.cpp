/*************************************************************************
	> File Name: 素数筛.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 10 May 2020 06:29:26 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int a[10005] = {0};

int main() {
	for (int i = 2; i < 1000; i++) {
		if (a[i]) continue;
		for (int j = 2; j * i < 1000; j++) {
			a[i * j] = 1;
		}
		cout << i << endl;
	}
	return 0;
}

