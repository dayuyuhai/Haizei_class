/*************************************************************************
	> File Name: 56-1.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 02 Jun 2020 06:59:48 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;
#define max_n 10

int a[max_n + 5] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

int main() {
	int x, y;
	cin >> x >> y;
	y -= 2;
	do {
		next_permutation(a, a + x);
	} while (y--);
	for (int i = 0; i < x; i++) {
		cout << a[i];
	}
	cout << endl;
	return 0;
}
