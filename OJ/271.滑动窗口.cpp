/*************************************************************************
	> File Name: 271.滑动窗口.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 23 Jun 2020 07:10:36 PM CST
 ************************************************************************/

#include<iostream>
#include<queue>
using namespace std;
#define max_n 300000

int a[max_n + 5];
int q[max_n + 5], head, tail;

int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	head = tail = 0;
	for (int i = 0; i < n; i++) {
		while (tail - head && a[i] < a[q[tail - 1]]) tail--;
		q[tail++] = i;
		if (i + 1 < k) continue;
		if (i - q[head] == k) head++;
		i + 1 == k || cout << ' ';
		cout << a[q[head]];
	}
	cout << endl;
	head = tail = 0;
	for (int i = 0; i < n; i++) {
		while (tail - head && a[i] >= a[q[tail - 1]]) tail--;
		q[tail++] = i;
		if (i + 1 < k) continue;
		if (i - q[head] == k) head++;
		i + 1 == k || cout << ' ';
		cout << a[q[head]];
	}
	cout << endl;
	return 0;
}
