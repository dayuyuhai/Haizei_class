/*************************************************************************
	> File Name: 213.分数段统计.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 17 May 2020 10:53:33 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

int a[35];
int b[10];

int cmp(int a, int b) {
	return a > b;
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		if (a[i] == 100) b[1]++;
		else if (a[i] >= 90) b[2]++;
		else if (a[i] >= 80) b[3]++;
		else if (a[i] >= 70) b[4]++;
		else if (a[i] >= 60) b[5]++;
		else b[6]++;
	}
	sort(a, a + n, cmp);
	for (int i = 0; i < n; i++) {
		cout << a[i] << endl;
	}
	for (int i = 1; i <= 6; i++) {
		!(i == 1) && cout << ' ';
		cout << b[i];
	}
	return 0;
}
