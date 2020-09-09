/*************************************************************************
	> File Name: 187.汉娜塔.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Fri 08 May 2020 03:57:40 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

long long f(int n) {
	if (n == 1) return 1;
	return 2 * f(n - 1) + 1;
}

long long g(int n) {
	if (n == 1) return 1;
	return 2 * g(n - 1) + n;
}

int main() {
	int n;
	cin >> n;
	cout << f(n) << ' ';
	cout << g(n) << endl;
	return 0;
}

