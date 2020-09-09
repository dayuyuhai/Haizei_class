/*************************************************************************
	> File Name: 143.数字游戏.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: Sun 03 May 2020 08:40:00 PM CST
 ************************************************************************/

#include<iostream>
#include<math.h>
using namespace std;

int isz(int x) {
	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0) return 0;
	}
	return 1;
}
	
int is(int x) {
	if (x % 6 != 0) return 0;
	if (!isz(x / 100)) return 0;
	x %= 100;
	if (pow(int(sqrt(double(x))), 2) - x) return 0;
	return 1;
}

int main() {
	int a, b, cnt = 0;
	cin >> a >> b;
	for (int i = a; i <= b; i++) {
		if (is(i)) {
			cnt++ && cout << ' ';
			cout << i;
		}
	}
	cout << endl;
	cout << cnt << endl;

	return 0;
}
