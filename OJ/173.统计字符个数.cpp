/*************************************************************************
	> File Name: 173.统计字符个数.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Fri 01 May 2020 04:36:35 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
	string s;
	getline(cin, s);
	int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == 32) cnt1++;
		else if ((s[i] >= 65 && s[i] <= 90) || (s[i] <= 122 && s[i] >= 97)) cnt2++;
		else if (s[i] >= 48 && s[i] <= 57) cnt3++;
		else cnt4++;
	}
	cout << cnt2 << ' ' << cnt3 << ' ' << cnt1 << ' ' << cnt4;

	return 0;
}

