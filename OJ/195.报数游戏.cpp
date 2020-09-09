/*************************************************************************
	> File Name: 195.报数游戏.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Wed 13 May 2020 03:25:28 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
int a[100005];

int main() {
	int n, m;
	cin >> n >> m;
	for (int i = 1; i <= n; i++) 
		scanf("%d", &a[i]);
	a[n + 1] = 100005;
	int flag = 0;
	int t;
	while (m--) {
		flag && cout << ' ';
		flag = 1;
		scanf("%d", &t);
		int l = 1, r = n;
		while (l != r) {
			int mid = (l + r + 1) >> 1;
			if (a[mid] > t) r = mid - 1;
			else l = mid;
		}
		cout << a[l];
	}
	return 0;
}
