/*************************************************************************
	> File Name: 43.数字三角形.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Thu 28 May 2020 06:05:10 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;
#define max_n 1000

int arr[max_n + 5][max_n + 5];

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j <= i; j++) {
			cin >> arr[i][j];
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j <= i; j++){
			arr[i][j] += max(arr[i + 1][j], arr[i + 1][j + 1]);
		}
	}
	cout << arr[0][0] << endl;
	return 0;
}
