/*************************************************************************
	> File Name: 444.插队问题.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Wed 13 May 2020 09:42:41 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#define max 100

int a[max + 5];

int main() {
	int n, x, temp;
	cin >> n;
	for (int i = 1; i <= n; i++) cin >> a[i];
	cin >> x;
	temp = a[n];
	for (int i = n; i > x; i--) {
		a[i] = a[i - 1];
	}
	a[x] = temp;
	for (int i = 1; i <= n; i++) {
		!(i == 1) && cout << ' ';
		cout << a[i];
	}
	
	return 0;
}
