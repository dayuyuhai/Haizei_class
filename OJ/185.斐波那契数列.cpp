/*************************************************************************
	> File Name: 185.斐波那契数列.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 09:57:42 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int f(int x) {
	if (x <= 2) return 1;
	return f(x - 1) + f(x - 2);
}
int main() {
	int x;
	cin >> x;
	cout << f(x) << endl;

	return 0;
}

