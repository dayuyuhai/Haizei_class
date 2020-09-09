/*************************************************************************
	> File Name: 310.阶乘分解.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 17 May 2020 10:55:13 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#define max_n 1000000
int a[max_n + 5];
int cnt[max_n + 5];

int n;

void init() {
	for (int i = 2; i <= n; i++) {
		if (!a[i]) a[++a[0]] = i;
		for (int j = 1; j <= a[0]; j++) {
			if (i * a[j] > n) break;
			a[a[j] * i] = 1;
			if (i % a[j] == 0) break;
		}
	}
	return;
}
int main() {
	cin >> n;
	init();
	int t;
	for (int i = n; i > 1; i--) {
		t = i;
		for (int j = 1; j <= a[0]; j++) {
			while (t % a[j] == 0) {
				cnt[j]++;
				t /= a[j];
			}
		}
	}
	for (int j = 1; j <= a[0]; j++) {
		!(cnt[j] == 0) && cout << a[j] << ' ' << cnt[j] << endl;
	}
	return 0;
}
