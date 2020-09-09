/*************************************************************************
	> File Name: 181.大小写翻转.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 08:03:47 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
	string s;
	cin >> s;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] >= 65 && s[i] <= 90) {
			cout << char(s[i] + 32);
		} else if (s[i] >= 97 && s[i] <= 122) {
			cout << char(s[i] - 32);
		} else cout << s[i];
	}
	return 0;
}
