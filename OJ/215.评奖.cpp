/*************************************************************************
	> File Name: 215.评奖.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Sat 02 May 2020 09:21:04 AM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

struct s{
	string name;
	int sum;
}student[45];

int cmp(struct s a, struct s b) {
	return a.sum > b.sum;
}

int main() {
	int n;
	cin >> n;
	int t1, t2, t3, t4;
	for (int i = 1; i <= n; i++) {
		cin >> student[i].name >> t1 >> t2 >> t3 >> t4;
		student[i].sum = t1 + t2 + t3 + t4;
	}
	sort(student + 1, student + 1 + n, cmp);
	for (int i = 1; i <= 3; i++) {
		cout << student[i].name << endl;
	}

	return 0;
}

