/*************************************************************************
	> File Name: 190.路飞的猜想.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Sun 03 May 2020 07:23:53 PM CST
 ************************************************************************/
#include<iostream>
using namespace std;
#define max_n 8000000
int a[8000005] = {0};

int init() {
	for (int i = 2; i * i <= max_n; i++) {
		if (a[i]) continue;
		for (int j = i * i; j < max_n; j += i) {
			a[j] = 1;
		}
	}
}

int main() {
	int n, cnt = 0;
	cin >> n;
	init();
	for (int i = 2; i <= n / 2; i++) {
		!a[i] && !a[n - i] && cnt++;
	}
	cout << cnt << endl;
	return 0;
}
