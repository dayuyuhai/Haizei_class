/*************************************************************************
	> File Name: 464.统计闰年.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Fri 08 May 2020 04:41:47 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int is(int y) {
	if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) return 1;
	return 0;
}

int main() {
	int x, y;
	cin >> x >> y;
	int cnt = 0;
	for (int i = x; i <= y; i++) {
		is(i) && cnt++;
	}
	cout << cnt << endl;
	return 0;
}
