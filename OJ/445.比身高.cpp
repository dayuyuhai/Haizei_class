/*************************************************************************
	> File Name: 445.比身高.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Wed 13 May 2020 11:52:46 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#define max 1000

int a[max], n;

int front(int x) {
	int cnt = 0;
	if (x == 0) return 0;
	for (int i = 0; i < x; i++) {
		if (a[i] > a[x]) cnt++;
	}
	return cnt;
}

int behind(int x) {
	int cnt = 0;
	if (x == n - 1) return 0;
	for (int i = x + 1; i < n; i++) {
		if (a[i] > a[x]) cnt++;
	}
	return cnt;
}

int main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		(front(i) == behind(i)) && cnt++;
	}
	cout << cnt << endl;
	return 0;
}
