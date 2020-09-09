/*************************************************************************
	> File Name: 177.字母图形.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 26 May 2020 10:33:18 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#include<queue>

int main() {
	queue <int> q;
	string s;
	cin >> s;
	for (int i = 0; i < s.length(); i++) {
		q.push(s[i]);
	}
	for (int i = 0; i < s.length(); i++) {
		int t = s.length() - 2;
		if (i) {
			while (t--) {
				q.push(q.front());
				q.pop();
			}
		}
		for (int j = 0; j < s.length(); j++) {
			cout << (char)q.front();
			q.push(q.front());
			q.pop();
		}
		cout << endl;
	}
	return 0;
}
