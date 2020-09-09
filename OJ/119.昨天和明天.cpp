/*************************************************************************
	> File Name: 119.昨天和明天.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Mon 11 May 2020 10:03:10 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int month[13] = {1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void before(int y, int m, int d){
	if (d == 1) {
		if (m == 1) {
			y--, m = 12, d = 31;
		} else if ((y % 4 == 0 && y % 100 != 0 || y % 400 == 0) && m == 3) {
			m--, d = month[m] + 1;
		} else m--, d = month[m];
	} else d--;
	cout << y << ' ' << m << ' ' << d << endl;
	return ;
}

void after(int y, int m, int d) {
	if ((y % 4 == 0 && y % 100 != 0 || y % 400 == 0) && m == 2) month[m]++;
	if (d == month[m]) {
		if (m == 12) {
			y++, m = 1, d = 1;
		} else {
			m++, d = 1;
		}
	} else d++;
	cout << y << ' ' << m << ' ' << d << endl;
	return ;
}

int main() {
	int y, m, d;
	cin >> y >> m >> d;
	before(y, m, d);
	after(y, m, d);
	return 0;
}
