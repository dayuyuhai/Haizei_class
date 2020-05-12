/*************************************************************************
	> File Name: 二分查找_数组变函数.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 12 May 2020 07:02:17 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#define max_n 100

int num(int n) {
	return n;
}

int flag = 1, ans = 0;
/*
int binary_search(int (*num)(int), int n, int x) {
	int head = 0, tail = n - 1, mid;
	while (head <= tail) {
		mid = (head + tail) >> 1;
		if (num(mid) == x) return mid;
		if (num(mid) < x) head = mid + 1;
		else tail = mid - 1;
	}
	return -1;
}
*/
int binary_search(int *arr, int x, int l, int r) {
	if (l > r) return -1;
	int mid = (l + r) >> 1;
	if (arr[mid] == x) {
		return mid;
	}
	if (arr[mid] < x) binary_search(arr, x, mid + 1, r);
	else binary_search(arr, x, l, mid - 1);
}
int main() {
	int arr[max_n + 5] = {0}, x;
	for (int i = 0; i < max_n; i++) arr[i] = i;
	while (~scanf("%d", &x)) {
		printf("search(%d) = %d\n", x, binary_search(arr, x, 0, max_n - 1));
	}
	return 0;
}

