/*************************************************************************
	> File Name: 2.list.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 07 Jun 2020 06:56:46 PM CST
 ************************************************************************/

#include<iostream>
#include<string.h>
#include<time.h>
using namespace std;

typedef struct ListNode {
	int data;
	struct ListNode *next;
} ListNode;

typedef struct List {
	ListNode head;
	int length;
} List;

ListNode *getNewNode(int);
List *getLinkList();
void clear_node(ListNode *);
void clear(List *);
int insert(List *, int, int);
int erase(List *, int);
void output(List *);
void output1(List *, int, int);
void reverse(List *);

int main() {
	srand(time(0));
	#define max_op 20
	List *l = getLinkList();
	int ind, op, val;
	for (int i = 0; i < max_op; i++) {
		op = rand() % 4;
		ind = rand() % (l->length + 3) - 1;
		cout << ind << endl;
		val = rand() % 10000;
		switch (op) {
			case 0:
			case 1: {
				printf("insert %d at %d to list = %d\n", val, ind, insert(l, ind, val));
			} break;
			case 2: {
				printf("erase a item at %d fro, list = %d\n", ind, erase(l, ind));
			} break;
			case 3: {
				printf("reverse the list !\n");
				reverse(l);
			} break;
		}
		output1(l, ind, op);
	}
	clear(l);
	#undef max_op
	return 0;
}

ListNode *getNewNode(int val) {
	ListNode *p = (ListNode *)malloc(sizeof(ListNode));
	p->data = val;
	p->next = NULL;
	return p;
}

List *getLinkList() {
	List *l = (List *)malloc(sizeof(List));
	l->head.next = NULL;
	l->length = 0;
	return l;
}

int insert(List *l, int ind, int val) {
	if (l == NULL) return 0;
	if (ind < 0 || ind > l->length) return 0;
	ListNode *p = &(l->head), *node = getNewNode(val);
	while (ind--) p = p->next;
	node->next = p->next;
	p->next = node;
	l->length += 1;
	return 1;
}

int erase(List *l, int ind) {
	if (l == NULL) return 0;
	if (ind < 0 || ind >= l->length) return 0;
	ListNode *p = &(l->head), *q;
	while (ind--) p = p->next;
	q = p->next;
	p->next = q->next;
	free(q);
	l->length -= 1;
	return 1;
}

void reverse(List *l) {
	ListNode *p = l->head.next, *q;
	l->head.next = NULL;
	while (p) {
		q = p->next;
		p->next = l->head.next;
		l->head.next = p;
		p = q;
	}
	return ;
}

void output(List *l) {
	printf("list(%d) = [", l->length);
	for (ListNode *p = l->head.next; p; p = p->next) {
		printf("%d->", p->data);
	}
	printf("NULL]\n");
	return ;
}

void output1(List *l, int ind, int op) {
	printf("head->");
	int cnt = 0;
	char str[100] = {0};	
	int i = 0;
	for (ListNode *p = l->head.next; p; p = p->next) {
		printf("%d->", p->data);
		if (i > ind) continue;
		i++;
		cnt += sprintf(str, "%d->", p->data);
	}
	printf("NULL\n");
	if (ind < 0 || ind > l->length || op == 3) cnt = 0;
	for (int i = 0; i < cnt + 3; i++) {
		printf(" ");
	}
	printf("^\n");
	for (int i = 0; i < cnt + 3; i++) {
		printf(" ");
	}
	printf("|\n\n");
}

void clear_node(ListNode *node) {
	if (node == NULL) return ;
	free(node);
	return ;
}

void clear(List *l) {
	if (l == NULL) return ;
	ListNode *p = l->head.next, *q;
	while (p) {
		q = p->next;
		clear_node(p);
		p = q;
	}
	free(l);
	return ;
}
