/*************************************************************************
	> File Name: 149.最后一个单词.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Wed 13 May 2020 12:00:43 PM CST
 ************************************************************************/

#include<iostream>
#include<string.h>
using namespace std;

int main() {
	string s;
	getline(cin, s);
	int cnt = 0;
	int i = s.size() - 1;
	while (s[i] != ' ') {
		cnt++;
		i--;
	}
	cout << cnt << endl;
	return 0;
}
