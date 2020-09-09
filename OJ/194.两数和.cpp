/*************************************************************************
	> File Name: 194.两数和.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Wed 13 May 2020 03:12:13 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
int a[100005];

int find(int x, int l, int r) {
	if (l > r) return 0;
	int mid = (l + r) >> 1;
	if (a[mid] == x) return 1;
	if (a[mid] > x) r = mid - 1;
	else l = mid + 1;
	find(x, l, r);
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	int s, flag = 0;
	cin >> s;
	for (int i = 1; i <= n; i++) {
		if(find(s - a[i], 1 + i, n)) {
			flag = 1; 
			break;
		}
	}
	cout << (flag ? "YES" : "NO") << endl;
	return 0;
}

