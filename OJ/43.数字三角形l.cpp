/*************************************************************************
	> File Name: 43.数字三角形l.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Thu 28 May 2020 06:20:58 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;
#define max_n 1000

int arr[max_n + 5][max_n + 5];
int keep[max_n + 5][max_n + 5];

int d(int i, int j, int n) {
	if (i + 1 == n) return arr[i][j];
	if (keep[i][j]) return keep[i][j];
	int val1 = d(i + 1, j, n);
	int val2 = d(i + 1, j + 1, n);
	return keep[i][j] = max(val1, val2) + arr[i][j]; 
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			cin >> arr[i][j];
		}
	}
	cout << d(0, 0, n) << endl;

	return 0;
}
