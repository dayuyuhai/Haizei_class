/*************************************************************************
	> File Name: 素数筛_zege.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 10 May 2020 06:31:25 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#define max_n 100

int prime[max_n + 5] = {0};

void init_prime() {
	for (int i = 2; i <= max_n; i++) {
		if (prime[i]) continue;
		prime[++prime[0]] = i;
		for (int j = i * i; j <= max_n; j += i) {
			prime[j] = 1;
		}
		//避免重复标记
	}
	return;
}
int main() {
	init_prime();
	for (int i = 1; i <= prime[0]; i++) {
		cout << prime[i] << endl;
	}
	return 0;
}
