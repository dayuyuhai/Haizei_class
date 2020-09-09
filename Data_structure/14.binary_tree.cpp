/*************************************************************************
	> File Name: 5.binary_tree.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Thu 25 Jun 2020 07:36:18 PM CST
 ************************************************************************/

#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

typedef struct Node {
	int data;
	struct Node *lchild, *rchild;
} Node;

typedef struct Tree {
	Node *root;
	int n;
} Tree;

Node *init_node(int val) {
	Node *p = (Node *)malloc(sizeof(Node));
	p->data = val;
	p->lchild = p->rchild = NULL;
	return p;
}

Tree *init_tree() {
	Tree *tree = (Tree *)malloc(sizeof(Tree));
	tree->root = NULL;
	tree->n = 0;
	return tree;
}

Node *insert_node(Node *root, int val, int *flag) {
	if (root == NULL) {
		*flag = 1;
		return init_node(val);
	}
	if (root->data == val) return root;
	if (val < root->data) root->lchild = insert_node(root->lchild, val, flag);
	else root->rchild = insert_node(root->rchild, val, flag);
	return root;
}

void insert(Tree *tree, int val) {
	int flag = 0;
	tree->root = insert_node(tree->root, val, &flag);
	tree->n += flag;
	return ;
}

void output_node(Node *root) {
	if (root == NULL) return ;
	printf("%d", root->data);
	if (root->lchild == NULL && root->rchild == NULL) return ;
	printf("(");
	output_node(root->lchild);
	printf(",");
	output_node(root->rchild);
	printf(")");
	return ;
}

void output(Tree *tree) {
	if (tree == NULL) return ;
	printf("Tree(%d) : ", tree->n);
	output_node(tree->root);
	printf("\n");
	return ;
}

void in_order_node(Node *root) {
	if (root == NULL) return ;
	in_order_node(root->lchild);
	printf("%d ", root->data);
	in_order_node(root->rchild);
	return ;
}

void in_order(Tree *tree) {
	if (tree == NULL) return ;
	printf("in_order : ");
	in_order_node(tree->root);
	printf("\n");
	return ;
}

void pre_order_node(Node *root) {
	if (root == NULL) return ;
	printf("%d ", root->data);
	pre_order_node(root->lchild);
	pre_order_node(root->rchild);
	return ;
}

void pre_order(Tree *tree) {
	if (tree == NULL) return ;
	printf("pre_order : ");
	pre_order_node(tree->root);
	printf("\n");
	return ;
}

void post_order_node(Node *root) {
	if (root == NULL) return ;
	post_order_node(root->lchild);
	post_order_node(root->rchild);
	printf("%d ", root->data);
	return ;
}

void post_order(Tree *tree) {
	if (tree == NULL) return ;
	printf("post_order : ");
	post_order_node(tree->root);
	printf("\n");
	return ;
}

void clear_node(Node *node) {
	if (node == NULL) return ;
	clear_node(node->lchild);
	clear_node(node->rchild);
	free(node);
	return ;
}

void clear(Tree * tree) {
	if (tree == NULL) return ;
	clear_node(tree->root);
	free(tree);
	return ;
}

int main() {
	srand(time(0));
	Tree *tree = init_tree();
	#define max_op 10
	for (int i = 0; i < max_op; i++) {
		int val = rand() % 100;
		insert(tree, val);
		output(tree);
	}
	pre_order(tree);
	post_order(tree);
	in_order(tree);
	#undef max_op
	clear(tree);
	return 0;
}
