/*************************************************************************
	> File Name: 145.最长的名字.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 08:10:12 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
	int n;
	string s;
	cin >> n;
	int max = 0;
	string p;
	while (n--) {
		cin >> s;
		if (s.size() > max) {
			p = s;
			max = s.size() > max ? s.size() : max;
		}
	}

	cout << p << endl;

	return 0;
}
