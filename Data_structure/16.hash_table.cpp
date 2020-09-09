/*************************************************************************
	> File Name: 15.hash_table.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sun 05 Jul 2020 08:07:59 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node {
	char *str;
	struct Node *next;
} Node;

typedef struct HashTable {
	Node **data;
	int size;
} HashTable;

Node *init_node(char *str, Node *head) {
	Node *p = (Node *)malloc(sizeof(Node));
	p->str = strdup(str);
	p->next = head;
	return p;
}

HashTable *init_hashtable(int n) {
	HashTable *h = (HashTable *)malloc(sizeof(HashTable));
	h->size = n << 1; 
	//hashtable利用率达不到%100
	h->data = (Node **)calloc(h->size, sizeof(Node *));
	return h;
}

int BKDRHash(char *str) {
	int seed = 31, hash = 0;
	for (int i = 0; str[i]; i++) hash = hash * seed + str[i];
	return hash & 0x7fffffff;
}

int insert(HashTable *h, char *str) {
	int hash = BKDRHash(str);
	int ind = hash % h->size;
	h->data[ind] = init_node(str, h->data[ind]);
	return 1;
}

int search(HashTable *h, char *str) {
	int hash = BKDRHash(str);
	int ind = hash % h->size;
	Node *p = h->data[ind];
	while (p && strcmp(p->str, str)) p = p->next;
	return p != NULL;
}

void clear_node(Node *node) {
	if (node == NULL) return ;
	Node *p = node, *q;
	while (p) {
		q = p->next;
		free(p->str);
		free(p);
		p = q;
	}
	free(q);
	return ;
}

void clear_hashtable(HashTable *h) {
	if (h == NULL) return ;
	for (int i = 0; i < h->size; i++) clear_node(h->data[i]);
	free(h->data);
	free(h);
	return ;
}


int main() {
	int op;
	#define max_n 100
	char str[max_n + 5] = {0};
	HashTable *h = init_hashtable(max_n + 5);
	while (~scanf("%d%s", &op, str)) {
		switch (op) {
			case 0:
				printf("insert %s to hash table\n", str);
				insert(h, str);
				break;
			case 1:
				printf("search %s from hash tablei result = %d\n", str, search(h, str));
				break;
		}
	}
	clear_hashtable(h);
	#undef max_n
	return 0;
}

