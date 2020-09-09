/*************************************************************************
	> File Name: 220.成绩排序.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Sat 02 May 2020 10:51:43 AM CST
 ************************************************************************/
#include<iostream>
#include<algorithm>
using namespace std;

struct str{
	string name;
	int t[6] = {0};
}s[105];

int c;

int cmp(struct str a, struct str b) {
	if (a.t[c] == b.t[c]) return a.name < b.name;
	return a.t[c] > b.t[c];
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> s[i].name;
		for (int j = 1; j <= 4; j++) {
			cin >> s[i].t[j];
			s[i].t[5] += s[i].t[j];
		}
	}
	for (int i = 1; i <= 5; i++) {
		c = i;
		sort(s + 1, s + 1 + n, cmp);
		for (int j = 1; j <= 4; j++) {
			if (j != 1) cout << ' ';
			cout << s[j].name;
		}
		cout << endl;
	}
	return 0;
}


