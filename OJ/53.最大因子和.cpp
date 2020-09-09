/*************************************************************************
	> File Name: 53.最大因子和.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Thu 28 May 2020 06:48:29 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;
#define max_n 1000000

int prime[max_n + 5];
int cnt[max_n + 5];
int f[max_n + 5];

void init() {
	for (int i = 2; i <= max_n; i++) {
		if (!prime[i]) {
			prime[++prime[0]] = i;
			cnt[i] = 1;
			f[i] = i + 1;
		}
		for (int j = 1; j <= prime[0]; j++) {
			if (i * prime[j] > max_n) break;
			prime[i * prime[j]] = 1;
			if (i % prime[j] == 0) {
				cnt[i * prime[j]] = cnt[i] + 1;
				f[i * prime[j]] = f[i] * (pow(prime[j], cnt[i] + 2) - 1) / (pow(prime[j], cnt[i] + 1) - 1);
				break;
			} else {
				cnt[i * prime[j]] = 1;
				f[i * prime[j]] = f[i] * f[prime[j]];
			}
		}
	}
}
int main() {
	init();
	int max = 0;
	for (int i = 0; i < max_n; i++) {
		if (f[i] > max) max = f[i];
	}
	cout << max << endl;

	return 0;
}
