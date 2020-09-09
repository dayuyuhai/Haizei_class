/*************************************************************************
	> File Name: 3.queue.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sat 20 Jun 2020 02:49:20 PM CST
 ************************************************************************/

#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

typedef struct Queue {
	int *data;
	int size, head, tail, cnt;
} Queue;

Queue *init(int n) {
	Queue *q = (Queue *)malloc(sizeof(Queue));
	q->data = (int *)malloc(sizeof(int) * n);
	q->size = n;
	q->head = q->tail = q->cnt = 0;
	return q;
}

int front(Queue *q) {
	return q->data[q->head];
}

int empty (Queue *q) {
	return q->cnt == 0;
}

int expand(Queue *q) {
	int extr_size = q->size;
	int *p;
	while (extr_size) {
		p = (int *)malloc(sizeof(int) * (q->size + extr_size));
		if (p) break;
		extr_size >>= 1;
	}
	if (p == NULL) return 0;
	for (int i = q->head, j = 0; j < q->cnt; j++) {
		p[j] = q->data[(i + j) % q->size];
	}
	free(q->data);
	q->data = p;
	q->size += extr_size;
	q->head = 0;
	q->tail = q->cnt;
	return 1;
}

int push(Queue *q, int val) {
	if (q == NULL) return 0;
	if (q->size == q->cnt) {
		if (!expand(q)) return 0;
		printf("\033[32m expand successful!\033[0m size = %d\n", q->size);
	}
	q->data[q->tail++] = val;
	q->cnt += 1;
	if (q->tail == q->size) q->tail -= q->size;
	return 1;
}

int pop(Queue *q) {
	if (q == NULL) return 0;
	if (empty(q)) return 0;
	q->head++;
	if (q->head == q->size) q->head -= q->size;
	q->cnt -= 1;
	return 1;
}

void output(Queue *q) {
	printf("Queue : [");
	for (int i = q->head, j = 0; j < q->cnt; j++) {
		j && printf(", ");
		printf("%d", q->data[(i + j) % q->size]);
	}
	printf("]\n");
	return ;
}

void clear(Queue *q) {
	if (q == NULL) return ;
	free(q->data);
	free(q);
	return ;
}

int main() {
	srand(time(0));
	#define max_op 5
	Queue *q = init(max_op);
	for (int i = 0; i < max_op + 20; i++) {
		int val = rand() % 100;
		int op = rand() % 4;
		switch (op) {
			case 0:
			case 1:
			case 2: {
				printf("push %d to the Queue = %d\n", val, push(q, val));
			} break;
			case 3: {
				printf("%d\n", q->head);
				printf("pop %d from the Queue = %d\n", front(q), pop(q));
			} break;
		}
		output(q), printf("\n");
	}
	#undef max_op
	clear(q);
	return 0;
}

