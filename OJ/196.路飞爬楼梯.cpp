/*************************************************************************
	> File Name: 196.路飞爬楼梯.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 10:10:29 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int f(int x) {
	if (x < 2) return 0;
	if (x <= 3) return 1;
	return f(x - 2) + f(x - 3);
}
int main() {
	int n;
	cin >> n;
	cout << f(n) << endl;

	return 0;
}
