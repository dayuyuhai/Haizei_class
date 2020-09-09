/*************************************************************************
	> File Name: 9.priority_queue.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sat 04 Jul 2020 03:23:35 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define swap(a, b) { \
	__typeof(a) tmp = a; \
	a = b, b = tmp; \
}

typedef struct priority_queue {
	int *data;
	int cnt, size;
} priority_queue;

priority_queue *init(int n) {
	priority_queue *q = (priority_queue *)malloc(sizeof(priority_queue));
	q->data = (int *)malloc(sizeof(int) * (n + 1));
	q->cnt = 0;
	q->size = n;
	return q;
}

int empty(priority_queue *q) {
	return q->cnt == 0;
}

int top(priority_queue *q) {
	return q->data[1];
}

int push(priority_queue *q, int val) {
	if (q == NULL) return 0;
	if (q->cnt == q->size) return 0;
	q->data[++(q->cnt)] = val;
	int ind = q->cnt;
	while (ind >> 1 && q->data[ind] > q->data[ind >> 1]) {
		swap(q->data[ind], q->data[ind >> 1]);
		ind >>= 1;
	}
	return 1;
}

int pop(priority_queue *q) {
	if (q == NULL) return 0;
	if (empty(q)) return 0;
	q->data[1] = q->data[q->cnt--];
	int ind = 1;
	while ((ind << 1) <= q->cnt) {
		int temp = ind, l = ind << 1, r = ind << 1 | 1;
		if (q->data[l] > q->data[temp]) temp = l;
		if (r <= q->cnt && q->data[r] > q->data[temp]) temp = r;
		if (temp == ind) break;
		swap(q->data[ind], q->data[temp]);
		ind = temp;
	}
	return 1;
}


void clear(priority_queue *q) {
	if (q == NULL) return ;
	free(q->data);
	free(q);
	return ;
}

int main() {
	srand(time(0));
	#define max_op 19
	priority_queue *q = init(max_op);
	for (int i = 0; i < max_op; i++) {
		int val = rand() % 100;
		push(q, val);
		printf("insert %d to priority_queue\n", val);
	}
	for (int i = 0; i < max_op; i++) {
		printf("%d ", top(q));
		pop(q);
	}
	printf("\n");
	clear(q);
	return 0;
}
