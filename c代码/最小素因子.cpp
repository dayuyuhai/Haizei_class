/*************************************************************************
	> File Name: su1.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 10 May 2020 07:16:17 PM CST
 ************************************************************************/
#include<iostream>
using namespace std;
#define max_n 100

int prime[max_n + 5] = {0};

void init_prime() {
	for (int i = 2; i <= max_n; i++) {
		if (prime[i]) continue;
		prime[i] = i;
		for (int j = i * i; j <= max_n; j += i) {
			if (prime[j]) continue;
			prime[j] = i;
		}
	}
	return;
}

int main() {
	init_prime();
	for (int i = 2; i <= max_n; i++) {
		printf("%d = %d\n", i, prime[i]);
	}
	return 0;
}

