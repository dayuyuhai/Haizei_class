/*************************************************************************
	> File Name: 219.交叉排序.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 17 May 2020 11:56:36 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

int cmp(int a, int b) {
	return a > b;
}

int main() {
	int n, l, r, l0, r0;
	cin >> n >> l >> r >> l0 >> r0;
	int a[10005];
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	sort(a + l, a + r + 1);
	sort(a + l0, a + r0 + 1, cmp);
	for (int i = 1; i <= n; i++) {
		!(i == 1) && cout << ' ';
		cout << a[i];
	}
	return 0;
}
