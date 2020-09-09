/*************************************************************************
	> File Name: 467.求阶乘.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Fri 08 May 2020 03:27:56 PM CST
 ************************************************************************/

#include<iostream>
#include<inttypes.h>
using namespace std;

int64_t mul(int x) {
	return x ? x * mul(x - 1) : 1;
}

int main() {
	int n;
	cin >> n;
	cout << mul(n) << endl;
	return 0;
}
