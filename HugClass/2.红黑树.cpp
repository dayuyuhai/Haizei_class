/*************************************************************************
	> File Name: 2.红黑树.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 24 Feb 2021 10:47:31 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

typedef struct Node {
    int key;
    int color;         // 0 red, 1 black, 2 double black
    Node *lchild, *rchild;
} Node;

#define NIL &__NIL

Node __NIL;

__attribute Generic() {
    __NIL->key = 0;
    __NIL->color = 1;
    __NIL->lchild = __NIL->rchild = __NIL;
}

Node *getNewNode(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->color = 0;
    node->lchild = node->rchild = NIL;
    return node;
}

Node *insert(Node root, int key) {
    if (root == NIL) return NIL;
    if (root->key == key) return root;
    if (root->key > key) root->lchild = insert(root->lchild);
    else root->rchild = insert(root->rchild);
}

Node *erase(Node root, int key) {
    if (root == NIL) return NIL;
    if (root->key > key) 
}

void clear(Node *root) {
    if (root == NIL) return NIL;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

int main() {


    return 0;
}
