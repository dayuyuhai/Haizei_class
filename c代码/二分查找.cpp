/*************************************************************************
	> File Name: 二分查找.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 12 May 2020 06:52:06 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#define max_n 100

int binary_search(int *num, int n, int x) {
	int head = 0, tail = n - 1, mid;
	while (head <= tail) {
		mid = (head + tail) >> 1;
		if (num[mid] == x) return mid;
		if (num[mid] < x) head = mid + 1;
		else tail = mid - 1;
	}
	return -1;
}

int main() {
	int arr[max_n + 5] = {0}, x;
	for (int i = 0; i < max_n; i++) arr[i] = i;
	while (~scanf("%d", &x)) {
		printf("search(%d) = %d\n", x, binary_search(arr, max_n, x));
	}
	return 0;
}
