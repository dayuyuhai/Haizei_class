/*************************************************************************
	> File Name: 二分查找10.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 24 May 2020 02:07:18 PM CST
 ************************************************************************/

#include<iostream>
#include<algorithm>
using namespace std;

// 111000
int binary_search1(int *arr, int n) {
	int head = -1, tail = n - 1, mid; //虚拟头
	while (head < tail) {
		mid = (head + tail + 1) >> 1;
		if (arr[mid] == 0) tail =  mid - 1;
		else head = mid;
	}
	return head;
}

// 000111
int binary_search2(int *arr, int n) {
	int head = 0, tail = n, mid;
	while (head < tail) {
		mid = (head + tail) >> 1;
		if (arr[mid] == 0) head = mid + 1;
		else tail = mid;
	}
	return (head == n ? -1 : head);
}

int main() {
	int num[10] = {0, 0, 0, 1, 1, 1, 1, 1, 1, 1};
	int a[10] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
	int b[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	cout << binary_search2(num, 10) << endl;
	return 0;
}
