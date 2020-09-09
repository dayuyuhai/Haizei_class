/*************************************************************************
	> File Name: 218.身高排序.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 17 May 2020 11:18:33 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

struct s {
	int k;
	int h;
}a[100005];

int cmp(struct s b, struct s c) {
	if (b.h == c.h) return b.k < c.k;
	return b.h < c.h;
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		a[i].k = i;
		cin >> a[i].h;
	}
	sort(a, a + n, cmp);
	for (int i = 0; i < n; i++) {
		(i) && cout << ' ';
		cout << a[i].k + 1;
	}
	return 0;
}
