/*************************************************************************
	> File Name: 537.门票问题.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sat 13 Jun 2020 01:37:12 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

char arr[31];
int keep[1000000];

int main() {
	int l, c;
	cin >> l >> c;
	for (int i = 0; i < c; i++) {
		cin >> arr[i];
	}
	sort(arr, arr + c);
	int j = 1, cnt;
	long long sum;
	do {
		sum = 0, cnt = 0;
		j++;
		for (int i = 0; i < l; i++) {
			sum += arr[i];
			if (arr[i] == 'a' || arr[i] == 'e' || arr[i] == 'i' || arr[i] == 'o' || arr[i] == 'u') cnt++;
		}
		if (keep[sum] || !cnt || l - cnt < 2) continue;
		for (int i = 0; i < l; i++) { 
			cout << arr[i];
		}
		cout << endl;
		keep[sum] = 1;
	} while (next_permutation(arr, arr + c) && j <= 25000);

	return 0;
}
