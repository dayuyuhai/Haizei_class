/*************************************************************************
	> File Name: 186.弹簧板.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 07:25:07 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int a[100005];

int ball(int n, int x, int p) {
	if (p >= n) return x - 1;
	return ball(n, x + 1, p + a[p]);
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	cout << ball(n, 1, 0) << endl;

	return 0;
}
