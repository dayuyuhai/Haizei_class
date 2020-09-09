/*************************************************************************
	> File Name: 176.寻找字符串.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 06:22:59 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;

int main() {
	string a, b;
	getline(cin, a);
	getline(cin, b);
	int cnt = 0;
	int pos;
	if (a.find(b) != -1) {
		pos = a.find(b);
		cnt++;
	}
	while (a.find(b, pos + 1) != -1) {
		pos = a.find(b, pos + 1);
		cnt++;
	}
	cout << cnt << endl;

	return 0;
}
