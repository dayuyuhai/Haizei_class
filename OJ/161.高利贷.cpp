/*************************************************************************
	> File Name: 161.高利贷.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Wed 27 May 2020 11:53:53 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
	int x, n;
	cin >> x >> n;
	double sum = x;
	while (n--) {
		sum = sum * (1.06);
	}
	printf("%.6lf\n", sum);
	return 0;
}
