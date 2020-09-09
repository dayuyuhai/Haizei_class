/*************************************************************************
	> File Name: 11.stable_sort.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 05 Jul 2020 03:16:58 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define swap(a, b) { \
	__typeof(a) tmp = a; \
	a = b, b = tmp; \
}

#define TEST(arr, n, func, args...) { \
	int *num = (int *)malloc(sizeof(int) * n); \
	memcpy(num, arr, sizeof(int) * n); \
	output(num, n); \
	printf("%s = ", #func); \
	func(args); \
	output(num, n); \
	free(num); \
}

void insert_sort(int *num, int n) {
	for (int i = 1; i < n; i++) {
		for (int j = i; j > 0 && num[j] < num[j - 1]; j--) {
			swap(num[j], num[j - 1]);
		}
	}
	return ;
}

void bubble_sort(int *num, int n) {
	int times = 1;
	for (int i = 1; i < n && times; i++) {
		times = 0;
		for (int j = 0; j < n - i; j++) {
			if (num[j] <= num[j + 1]) continue;
			swap(num[j], num[j + 1]);
			times++;
		}
	}
	return ;
}

void merge_sort(int *num, int l, int r) {
	if (r - l <= 1) {
		if (r - l == 1 && num[r] < num[l]) {
			swap(num[l], num[r]);
		}
		return ;
	}
	int mid = (l + r) >> 1;
	merge_sort(num, l, mid);
	merge_sort(num, mid + 1, r);
	int *temp = (int *)malloc(sizeof(int) * (r - l + 1));
	int p1 = l, p2 = mid + 1, k = 0;
	while (p1 <= mid || p2 <= r) {
		if (p2 > r || (p1 <= mid && num[p1] <= num[p2])) {
			temp[k++] = num[p1++];
		} else {
			temp[k++] = num[p2++];
		}
	}
	memcpy(num + l, temp, sizeof(int) * (r - l + 1));
	free(temp);
	return ;
}

void randint(int *num, int n) {
	while (n--) num[n] = rand() % 100;
	return ;
}

void output(int *num, int n) {
	printf("[");
	for (int i = 0; i < n; i++) printf("%d ", num[i]);
	printf("]\n");
	return ;
}

int main() {
	srand(time(0));
	#define max_op 20
	int arr[max_op];
	randint(arr, max_op);
	TEST(arr, max_op, insert_sort, num, max_op);
	TEST(arr, max_op, bubble_sort, num, max_op);
	TEST(arr, max_op, merge_sort, num, 0, max_op - 1);
	#undef max_op
	return 0;
}
