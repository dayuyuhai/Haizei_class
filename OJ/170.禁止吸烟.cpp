/*************************************************************************
	> File Name: 170.禁止吸烟.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 05:41:30 PM CST
 ************************************************************************/

#include<iostream>
#include<string>
using namespace std;

int main() {
	int n;
	cin >> n;
	string s;
	for (int i = 0; i < n; i++) {
		cin >> s;
		while (s.find("Ban_smoking") != -1) {
			int pos = s.find("Ban_smoking");
			s.replace(pos, 11, "No_smoking");
		}
		cout << s << endl;
	}

	return 0;
}
