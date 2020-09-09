/*************************************************************************
	> File Name: 447.幸运数的划分.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Wed 13 May 2020 10:15:03 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int is_luck(int y) {
	while (y) {
		int t = y % 10;
		if (t % 7 != 0 && t % 4 != 0) return 0;
		y /= 10;
	}
	return 1;
}


int is_v(int x) {
	int y;
	for (int i = 1; i <= x; i++) {
		(x % i == 0) && (y = x / i);
		if (is_luck(y)) return 1;
	}
	return 0;
}
int main() {
	int n;
	cin >> n;
	cout << (is_v(n) ? "YES" : "NO") << endl;
	return 0;
}
