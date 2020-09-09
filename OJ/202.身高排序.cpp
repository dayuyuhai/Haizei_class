/*************************************************************************
	> File Name: 202.身高排序.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Sat 02 May 2020 08:54:33 AM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

struct s{
	int height;
	int index;
}student[1005];

int cmp(struct s a, struct s b) {
	if (a.height == b.height) return a.index < b.index;
	return a.height < b.height;
}

int main() {
	int n;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> student[i].height;
		student[i].index = i;
	}
	sort(student + 1, student + 1 + n, cmp);
	for (int i = 1; i <= n; i++) {
		if (i != 1) cout << ' ';
		cout << student[i].index;
	}

	return 0;
}
