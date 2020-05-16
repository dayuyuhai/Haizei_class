/*************************************************************************
	> File Name: 线性筛.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sat 16 May 2020 06:37:48 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#define max_n 200000

int a[max_n + 5];

int main() {
	for (int i = 2; i <= max_n; i++) {
		if (!a[i]) a[++a[0]] = i;
		for (int j = 1; j <= a[0]; j++) {
			if (i * a[j] > max_n) break;
			a[i * a[j]] = 1;
			if (i % a[j] == 0) break;
		}
	}
	cout << a[10001] << endl;
	return 0;
}
