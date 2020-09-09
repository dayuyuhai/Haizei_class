/*************************************************************************
	> File Name: 201.香克斯的随机数.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 26 May 2020 09:32:00 AM CST
 ************************************************************************/

#include<iostream>
#include<set>
using namespace std;
#define max_n 100

int a[max_n + 5];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	set<int> s(a, a + n);
	cout << s.size() << endl;
	int flag = 0;
	for (set<int>::iterator it = s.begin(); it != s.end(); it++) {
		(flag) && cout << ' ';
		cout << *it;
		flag = 1;
	}
	cout << endl;
	return 0;
}
