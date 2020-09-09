/*************************************************************************
	> File Name: 216.获取姓名并排序.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 17 May 2020 08:50:16 PM CST
 ************************************************************************/

#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	string s[105];
	for (int i = 0; i < n; i++) {
		cin >> s[i];
		s[i] = s[i].substr(3, s[i].length() - 1);
	}
	sort(s, s + n);
	for (int i = 0; i < n; i++) {
		cout << s[i] << endl;
	}
	return 0;
}
