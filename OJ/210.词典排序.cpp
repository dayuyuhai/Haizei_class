/*************************************************************************
	> File Name: 210.词典排序.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 24 May 2020 02:45:04 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

string s[30];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> s[i];
	}
	sort(s, s + n);
	for (int i = 0; i < n; i++) {
		(i) && cout << ' ';
		cout << s[i];
	}
	return 0;
}
