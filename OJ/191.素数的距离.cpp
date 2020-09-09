/*************************************************************************
	> File Name: 191.素数的距离.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Wed 13 May 2020 06:37:49 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
int arr[8000005];

void init() {
	for (int i = 2; i * i < 8000000; i++) {
		if (arr[i]) continue;
		for (int j = i * i; j < 8000000; j += i) {
			arr[j] = 1;
		}
	}
	return;
}

int main() {
	int l, r;
	cin >> l >> r;
	init();
	if (l < 2) l = 2;
	int flag = 0;
	int a, b, c, d;
	for (int i = l; i <= r; i++) {
		if (!arr[i]) {
			int next = i + 1;
			while (arr[next]) next++;
			if (next > r) break;
			if (flag == 0) {
				a = c = i;
				b = d = next;
			}
			if (b - a > next - i) {
				a = i;
				b = next;
			} else if (d - c < next - i) {
				c = i;
				d = next;
			}
			flag = 1;
		}
	}
	if (flag) printf("%d,%d are closest, %d,%d are most distant.", a, b, c, d);
	else printf("There are no adjacent primes.");
	return 0;
}
