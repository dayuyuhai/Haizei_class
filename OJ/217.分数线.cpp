/*************************************************************************
	> File Name: 217.分数线.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 17 May 2020 11:06:05 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

int a[100005];

int cmp(int a, int b) {
	return a > b;
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a, a + n, cmp);
	int k, cnt = 0;
	if (n & 1) k = n / 2;
	else k = n / 2 - 1;
	cout << a[k] << ' ';
	for (int i = k; i < n; i++) {
		if (a[i] == a[k]) cnt++;
	}
	cout << k + cnt << endl;
	return 0;
}
