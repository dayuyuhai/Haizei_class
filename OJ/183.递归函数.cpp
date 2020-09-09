/*************************************************************************
	> File Name: 183.递归函数.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 09:53:42 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int f(int x) {
	if (x <= 0) return 0;
	if (x == 1) return 1;
	if (x & 1 == 1) x++;
	return 3 * f(x / 2) - 1;
}
int main() {
	int x;
	cin >> x;
	cout << f(x) << endl;

	return 0;
}
