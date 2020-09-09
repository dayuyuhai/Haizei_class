/*************************************************************************
	> File Name: 1.Vector.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sat 06 Jun 2020 07:51:31 PM CST
 ************************************************************************/

#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

typedef struct Vector {
	int *data;
	int size, length;
} Vector;

Vector *init(int n) {
	Vector *vec = (Vector *) malloc(sizeof(Vector));
	vec->data = (int *)malloc(n * sizeof(int));
	vec->size = n;
	vec->length = 0;
	return vec;
}

int expand(Vector *vec) {
	//vec->size *= 2;
	//vec->data = (int *)realloc(vec->data, sizeof(int) * vec->size)
    //开辟失败(内存哪哪都没地方)返回NULL，会内存泄漏,原来的数据找不到了
	int extr_size = vec->size;
	int *p;
	while (extr_size) {
		p = (int *)realloc(vec->data, sizeof(int) * (vec->size + extr_size));
		if (p) break;
		extr_size /= 2;
	}
	if (extr_size == 0) return 0;
	vec->data = p;
	vec->size += extr_size;
	return 1;
}

/*
 * malloc   返回开辟空间的首地址
 * calloc   开辟空间，并都清空为0
 * realloc  重新开辟空间，先看当前地址后面够不够开，不够就从内存换一个地方分配空间，之前数据拷贝过去
 */

//智能指针

int insert(Vector *vec, int ind, int val) {
	if (vec == NULL) return 0;
	if (ind < 0 || ind > vec->length) return 0;
	if (vec->length == vec->size) {
		if (!expand(vec)) return 0;
		printf("success to expand ! the Vector size is %d\n", vec->size);
	}
	for (int i = vec->length; i > ind; i--) {
		vec->data[i] = vec->data[i - 1];
	}
	vec->data[ind] = val;
	vec->length += 1;
	return 1;
}

int erase(Vector *vec, int ind) {
	if (vec == NULL) return 0;
	if (ind < 0 || ind >= vec->length) return 0;
	for (int i = ind + 1; i < vec->length; i++) {
		vec->data[i - 1] = vec->data[i];
	}
	vec->length -= 1;
	return 1;
}

void output(Vector *vec) {
	printf("Vector : [");
	for (int i = 0; i < vec->length; i++) {
		i && printf(", ");
		printf("%d", vec->data[i]);
	}
	printf("]\n");
}

void clear(Vector *vec) {
	free(vec->data);
	free(vec);
	return ;
}

int main() {
	srand(time(0));
    #define max_op 20
	Vector *vec = init(max_op);
	for (int i = 0; i < max_op << 2; i++) {
		int op = rand() % 4;
		int ind = rand() % (vec->length + 3) - 1;
		int val = rand() % 100;
		switch (op) {
			case 0:
			case 1:
			case 2: {
				printf("insert %d at %d to Vector = %d\n", val, ind, insert(vec, ind, val));
			} break;
			case 3: {
				printf("erase a item at %d from Vector = %d\n", ind, erase(vec, ind));
			} break;
		}
		output(vec);
		printf("\n");
	}
	output(vec);
	clear(vec);
	#undef max_op
	return 0;
}
