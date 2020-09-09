/*************************************************************************
	> File Name: 271.1.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 23 Jun 2020 08:15:44 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#include<queue>
#define max_n 300000

int a[max_n + 5];

int main() {
	int n, k;
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	queue<int> q;
	for (int i = 0; i < n; i++) {
		while (q.empty() || a[i] < a[q.back()]) q.push(i);
		if (q.size() == 2 && q.front() - q.back() < k) q.pop();
		cout << a[q.front()] << ' ';
	}
	cout << endl;
	return 0;
}
