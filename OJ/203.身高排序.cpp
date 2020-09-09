/*************************************************************************
	> File Name: 203.身高排序.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 26 May 2020 10:10:31 AM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;
#define max_n 100

int a[max_n + 5];

int cmp(int a, int b) {
	return a > b;
}
int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m * n; i++) {
		cin >> a[i];
	}
	int maxx;
	for (int j = 0; j < m; j++) {
		maxx = a[j];
		for (int i = j; i < m * n; i += m) {
			if (maxx < a[i]) maxx = a[i];
		}
		cout << maxx << endl;
	}
	sort(a, a + n * m, cmp);
	double sum = 0;
	for (int i = 0; i < m * n; i++) {
		sum += a[i];
		(i) && cout << ' ';
		cout << a[i];
	}
	cout << endl;
	sum /= (m * n);
	int res = (int)(sum + 0.5);
	cout << res << endl;
	int i = 0;
	while (a[i] >= res) i++;
	cout << i << endl;
	return 0;
}
