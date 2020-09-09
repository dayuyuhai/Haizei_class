/*************************************************************************
	> File Name: 189.实现折半查找.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Wed 13 May 2020 09:02:38 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#include<iostream>
using namespace std;
#define max_n 1000000
int a[max_n + 5];

int is_v(int t, int n) {
	int head = 1, tail = n;
	while (head <= tail) {
		int mid = (head + tail) >> 1;
		if (a[mid] == t) return mid;
		if (a[mid] > t) tail = mid - 1;
		else head = mid + 1;
	}
	return 0;
}

int main() {
	int n, k, t;
	cin >> n >> k;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (int j = 0; j < k; j++) {
		scanf("%d", &t);
		if (j) cout << ' ';
		cout << is_v(t, n);
	}
	return 0;
}

