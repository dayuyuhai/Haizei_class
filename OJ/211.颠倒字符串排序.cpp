/*************************************************************************
	> File Name: 211.颠倒字符串排序.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 24 May 2020 08:56:52 PM CST
 ************************************************************************/

#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
#define max_n 30

string s[max_n + 5];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> s[i];
		reverse(s[i].begin(), s[i].end());
	}
	sort(s, s + n);
	for (int i = 0; i < n; i++) {
		cout << s[i] << endl;
	}
	return 0;
}
