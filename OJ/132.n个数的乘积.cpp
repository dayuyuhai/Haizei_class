/*************************************************************************
	> File Name: 132.n个数的乘积.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Mon 11 May 2020 10:40:40 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
	int n, x;
	cin >> n;
	long long ans = 1;
	for (int i = 0; i < n; i++) {
		cin >> x;
		ans *= x;
	}
	cout << ans << endl;
	return 0;
}
