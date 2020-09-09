/*************************************************************************
	> File Name: 187.汉娜塔2.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Fri 08 May 2020 04:23:44 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

long long f(int n, long long &w) {
	long long ret;
	if (n == 1) {
		w = 1;
		return 1;
	}
	ret = 2 * f(n - 1, w) + 1;
	w = 2 * w + n;
	return ret;
}

int main() {
	int n;
	long long w;
	cin >> n;
	cout << f(n, w) << ' ';
	cout << w << endl;
	return 0;
}

