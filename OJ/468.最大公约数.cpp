/*************************************************************************
	> File Name: 468.最大公约数.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Fri 08 May 2020 03:23:36 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int main() {
	int a, b;
	cin >> a >> b;
	cout << gcd(a, b) << endl;

	return 0;
}
