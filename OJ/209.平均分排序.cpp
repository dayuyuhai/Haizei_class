/*************************************************************************
	> File Name: 209.平均分排序.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 24 May 2020 02:38:07 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

double a[105];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	sort(a, a + n);
	for (int i = 0; i < n; i++) {
		cout << a[i] << endl;
	}
	return 0;
}
