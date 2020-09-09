/*************************************************************************
	> File Name: 187.汉娜塔3.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Fri 08 May 2020 04:29:48 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

void f(long long &t, long long &w, int n) {
	if (n == 1) {
		t = 1;
		w = 1;
		return ;
	}
	f(t, w, n - 1);
	t = 2 * t + 1;
	w = 2 * w + n;
	return ;
}

int main() {
	int n;
	long long t, w;
	cin >> n;
	f(t, w, n);
	cout << t << ' ' << w << endl;
	return 0;
}

