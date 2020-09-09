/*************************************************************************
	> File Name: 10.heap_sort.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sat 04 Jul 2020 06:41:01 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define swap(a, b) { \
	__typeof(a) tmp = a; \
	a = b, b = tmp; \
}

void downUpdate(int *arr, int n, int ind) {
	while (ind << 1 <= n) {
		int temp = ind, l = ind << 1, r = ind << 1 | 1;
		if (arr[l] > arr[temp]) temp = l;
		if (r <= n && arr[r] > arr[temp]) temp = r;
		if (temp == ind) break;
		swap(arr[temp], arr[ind]);
		ind = temp;
	}
	return ;
}

void heap_sort(int *arr, int n) {
	arr -= 1;
	for (int i = n >> 1; i >= 1; i--) {
		downUpdate(arr, n, i);
	}
	for (int i = n; i > 1; i--) {
		swap(arr[i], arr[1]);
		downUpdate(arr, i - 1, 1);
	}
}

void output(int *arr, int n) {
	printf("arr[%d] = [", n);
	for (int i = 0; i < n; i++) {
		printf(" %d", arr[i]);
	}
	printf("]\n");
	return ;
}

int main() {
	srand(time(0));
	#define max_op 20
	int *arr = (int *)malloc(sizeof(int) * max_op);
	for (int i = 0; i < max_op; i++) {
		arr[i] = rand() % 100;
	} 
	output(arr, max_op);
	heap_sort(arr, max_op);
	output(arr, max_op);
	free(arr);
	return 0;
}

