/*************************************************************************
	> File Name: 线性筛欧拉11.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sat 16 May 2020 07:28:07 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#define max_n 2000000

int a[max_n + 5];

int main() {
	long long sum = 0;
	for (int i = 2; i < max_n; i++) {
		if(!a[i]) a[++a[0]] = i;
		for (int j = 1; j <= a[0]; j++) {
			if (i * a[j] > max_n) break;
			a[i * a[j]] = 1;
			if (i % a[j] == 0) break;
		}
	}
	for (int i = 1; i <= a[0]; i++) {
		sum += a[i];
	}
	cout << sum << endl;
	return 0;
}
