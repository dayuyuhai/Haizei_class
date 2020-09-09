/*************************************************************************
	> File Name: 207.评奖2.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Sat 02 May 2020 10:03:08 AM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

struct str{
	string name;
	int t[5] = {0};
}s[35];

int cmp(struct str a, struct str b) {
	return a.t[0] > b.t[0];
}

int main() {
	int n;
	cin >> n;
	int maxx = 0;
	int minn = 300;
	for (int i = 1; i <= n; i++) {
		cin >> s[i].name;
		for (int j = 1; j <= 4; j++) {
			cin >> s[i].t[j];
			maxx = max(s[i].t[j], maxx);
			minn = min(s[i].t[j], minn);
			s[i].t[0] += s[i].t[j];
		}
		cout << s[i].t[0] << endl;
	}
	sort(s + 1, s + 1 + n, cmp);
	cout << s[1].name << endl;
	cout << maxx << ' ' << minn << endl;
	return 0;
}


