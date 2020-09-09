/*************************************************************************
	> File Name: 168.规范化名字.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 08:27:13 AM CST
 ************************************************************************/

#include<iostream>
#include<cctype>
#include<algorithm>
using namespace std;

string s[105];

int main() {
	int n;
	cin >> n;
	string str;
	for (int i = 0; i < n; i++) {
		cin >> str;
		for (int j = 0; j < str.length(); j++) {
			if (j == 0) str[j] = toupper(str[j]);
			else str[j] = tolower(str[j]);
		}
		s[i] = str;
	}
	sort(s, s + n);
	for (int i = 0; i < n; i++) {
		cout << s[i] << endl;
	}


	return 0;
}

