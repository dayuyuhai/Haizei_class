/*************************************************************************
	> File Name: 15.binary_search.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 05 Jul 2020 07:21:36 PM CST
 ************************************************************************/

#include<stdio.h>

#define P(func, args...) { \
	printf("%s = %d\n", #func, func(args)); \
}

// 2 3 4 5 7
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

// 11111111000000
int binary_search1(int *num, int n) {
	int head = -1, tail = n - 1, mid;
	while (head < tail) {
		mid = (head + tail + 1) >> 1;
		if (num[mid] == 1) head = mid;
		else tail = mid - 1;
	}
	return head;
}

// 00000000111111
int binary_search2(int *num, int n) {
	int head = 0, tail = n, mid;
	while (head < tail) {
		mid = (head + tail) >> 1;
		if (num[mid] == 1) tail = mid;
		else head = mid + 1;
	}
	return head == n ? -1 : head;
}

int main() {
	int arr1[10] = {2, 3, 4, 5, 7, 9, 32, 43, 111, 121};
	int arr2[10] = {1, 1, 1, 1, 0, 0, 0, 0, 0, 0};
	int arr3[10] = {0, 0, 0, 0, 1, 1, 1, 1, 1, 1};
	P(binary_search, arr1, 10, 7);
	P(binary_search1, arr2, 10);
	P(binary_search2, arr3, 10);
	return 0;
 }
