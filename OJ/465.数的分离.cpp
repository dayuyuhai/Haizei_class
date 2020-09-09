/*************************************************************************
	> File Name: 465.数的分离.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Fri 08 May 2020 03:38:05 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int digit(long long n, int k) {
	if (n == 0) return 0;
	if (k == 1) return n % 10;
	return digit(n / 10, k - 1);
}

int main() {
	long long n;
	int k;
	cin >> n >> k;	
	cout << digit(n, k) << endl; 
	return 0;
}
