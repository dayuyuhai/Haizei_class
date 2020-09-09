/*************************************************************************
	> File Name: 147.大数的奇偶性判断.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Wed 13 May 2020 12:08:07 PM CST
 ************************************************************************/

#include<iostream>
#include<string.h>
using namespace std;

int main() {
	string s;
	cin >> s;
	cout << ((s[s.size() - 1] % 2 == 0) ? "YES" : "NO") << endl;
	return 0;
}
