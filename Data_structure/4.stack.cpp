/*************************************************************************
	> File Name: 4.stack.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 21 Jun 2020 03:31:18 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Stack {
	int *data;
	int top, size;
} Stack;

Stack *init(int);
void clear(Stack *);
int top(Stack *);
int empty(Stack *);
int push(Stack *, int);
int pop(Stack *);
void output(Stack *);
int expand(Stack *);

int main() {
	srand(time(0));
	#define max_op 2
	Stack *s = init(max_op);
	for (int i = 0; i < max_op + 20; i++) {
		int op = rand() % 4;
		int val = rand() % 100;
		switch (op) {
			case 0:
			case 1:
			case 2:
				printf("push %d to the stack = %d\n", val, push(s, val));
				break;
			case 3:
				printf("pop %d from the stack = %d\n", top(s), pop(s));
				break;
		}
		output(s), printf("\n");
	}
	clear(s);
	return 0;
}

Stack *init(int n) {
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->data = (int *)malloc(sizeof(int) * n);
	s->size = n;
	s->top = -1;
	return s;
}

int top(Stack *s) {
	return s->data[s->top];
}

int empty(Stack *s) {
	return s->top == -1;
}

int expand(Stack *s) {
	int *p;
	int extr_size = s->size;
	while (extr_size) {
		p = (int *)realloc(s->data, sizeof(int) * (s->size + extr_size));
		if (p) break;
		extr_size /= 2;
	}
	if (!extr_size) return 0;
	s->data = p;
	s->size += extr_size;
	return 1;
}

int push(Stack *s, int val) {
	if (s == NULL) return 0;
	if (s->top + 1 == s->size) {
		printf("expand %s\n", expand(s) ? "success" : "failed");
	}
	s->data[++(s->top)] = val;
	return 1;
}

int pop(Stack *s) {
	if (s == NULL) return 0;
	if (empty(s)) return 0;
	s->top--;
	return 1;
}

void output(Stack *s) {
	printf("Stack(%d) = [", s->size);
	for (int i = 0; i <= s->top; i++) {
		i && printf(", ");
		printf("%d", s->data[i]);
	}
	printf("]\n");
	return ;
}

void clear(Stack *s) {
	if (s == NULL) return ;
	free(s->data);
	free(s);
	return ;
}

