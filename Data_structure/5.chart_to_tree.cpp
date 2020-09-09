/*************************************************************************
	> File Name: 5.chart_to_tree.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sat 27 Jun 2020 02:16:33 PM CST
 ************************************************************************/

#include<iostream>
#include<string.h>
#include<stack>
using namespace std;

typedef struct node {
	char data;
	struct node *lchild, *rchild;
} Node;

typedef struct tree {
    Node *root;
	int n;
} Tree;

typedef struct Stack {
	Node **data;
	int top, size;
} Stack;

Node *getNewNode(char val) {
	Node *p = (Node *)malloc(sizeof(Node));
	p->data = val;
	p->lchild = p->rchild = NULL;
	return p;
}

Tree *getNewTree() {
	Tree *tree = (Tree *)malloc(sizeof(Tree));
	tree->root = NULL;
	tree->n = 0;
	return tree;
}

Stack *init_stack(int n) {
	Stack *s = (Stack *)malloc(sizeof(Stack));
	s->data = (Node **)malloc(n * sizeof(Node *));
	s->size = n;
	s->top = -1;
	return s;
}

Node *top(Stack *s) {
	return s->data[s->top];
}

int empty(Stack *s) {
	return s->top == -1;
}

int push(Stack *s, Node *val) {
	if (s == NULL) return 0;
	if (s->top == s->size - 1) return 0;
	s->data[++(s->top)] = val;
	return 1;
}

int pop(Stack *s) {
	if (s == NULL) return 0;
	if (empty(s)) return 0;
	s->top--;
	return 1;
}

void pre_order(Node *root) {
	if (root == NULL) return ;
	printf("%c ", root->data);
	pre_order(root->lchild);
	pre_order(root->rchild);
	return ;	
}

void in_order(Node *root) {
	if (root == NULL) return ;
	in_order(root->lchild);
	printf("%c ", root->data);
	in_order(root->rchild);
	return ;	
}

void post_order(Node *root) {
	if (root == NULL) return ;
	post_order(root->lchild);
	post_order(root->rchild);
	printf("%c ", root->data);
	return ;	
}

void pre_order_tree(Tree *tree) {
	if (tree == NULL) return ;
	printf("pre_order : ");
	pre_order(tree->root);
	printf("\n");
	return ;
}

void in_order_tree(Tree *tree) {
	if (tree == NULL) return ;
	printf("in_order : ");
	in_order(tree->root);
	printf("\n");
	return ;
}

void post_order_tree(Tree *tree) {
	if (tree == NULL) return ;
	printf("pre_order : ");
	post_order(tree->root);
	printf("\n");
	return ;
}

void clear_stack(Stack *s) {
	if(s == NULL) return ;
	free(s->data);
	free(s);
	return ;
}

void clear_node(Node *root) {
	if (root == NULL) return ;
	clear_node(root->lchild);
	clear_node(root->rchild);
	free(root);
	return ;
}

void clear_tree(Tree *tree) {
	if (tree == NULL) return ;
	clear_node(tree->root);
	free(tree);
	return ;
}

Node *build(const char *str, int *node_num) {
	Stack *s = init_stack(strlen(str));
	Node *temp = NULL, *p = NULL;
	int flag = 0;
	*node_num = 0;
	while (str[0]) {
		switch (str[0]) {
			case '(':
				push(s, temp);
				flag = 0;
				break;
			case ')':
				p = top(s);
				pop(s);
				flag = 0;
				break;
			case ',':
				flag = 1;
				break;
			case ' ':
				break;
			default:
				temp = getNewNode(str[0]);
				if (!empty(s) && flag == 0) {
					top(s)->lchild = temp;
				} else if (!empty(s) && flag) {
					top(s)->rchild = temp;
				}
				++(*node_num);
				break;
		}
		++str;
	}
	clear_stack(s);
	if (temp && !p) p = temp;
	return p;
}


int main() {
	char str[1000] = {0};
	int node_num;
	scanf("%[^\n]", str);
	Tree *tree = getNewTree();
	tree->root = build(str, &node_num);
	tree->n = node_num;
	pre_order_tree(tree);
	in_order_tree(tree);
	post_order_tree(tree);
	clear_tree(tree);
	return 0;
}
