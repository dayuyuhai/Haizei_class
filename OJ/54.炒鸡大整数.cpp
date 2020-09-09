/*************************************************************************
	> File Name: ab.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sat 23 May 2020 04:42:02 PM CST
 **********************************************************************/
#include<iostream>
#include<string.h>
using namespace std;
#define max_n 1500

int a[max_n];
int sum[max_n + 5];

void carry(int *arr) {
	for (int k = 1; k <= arr[0]; k++) {
		if (arr[k] < 10) continue;
		arr[k + 1] += arr[k] / 10;
		arr[k] %= 10;
		arr[0] += (k == arr[0]);
	}
}

int main() {
	int x;
	while (scanf("%d", &x) != EOF){
		memset(a, 0, sizeof(a));
		memset(sum, 0, sizeof(sum));
		a[0] = 1, a[1] = 1;
		sum[0] = 1, sum[1] = 1;
		for (int i = 1; i <= x; i++) {
			for (int j = 1; j <= a[0]; j++) {
				a[j] *= i;
			}
			carry(a);
			
		}
		
		for (int i = 1; i <= a[0]; i++) {
			if (a[i] == 0) continue;
			for (int j = 1; j <= sum[0]; j++) {
				sum[j] *= a[i];
			}
			carry(sum);
		}
		for (int i = sum[0]; i > 0; i--) cout << sum[i];
		cout << endl;
	}

	return 0;
}
