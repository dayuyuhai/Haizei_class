/*************************************************************************
	> File Name: 174.批量替换字符串.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 09:23:32 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;

int main() {
	string s;
	getline(cin, s);
	for (int i = 0; i < s.length(); i++) {
		if (s[i]== ' ') s.replace(i, 1, "%20");
	}
	cout << s << endl;

	return 0;
}
