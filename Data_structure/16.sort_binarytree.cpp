/*************************************************************************
	> File Name: 16.sort_binarytree.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 21 Jul 2020 07:03:13 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Node {
    int data;
    Node *lchild, *rchild;
} Node;

Node *init(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = val;
    node->lchild = node->rchild = NULL;
    return node;
}

Node *search(Node *node, int val) {
    if (node == NULL || node->data == val) return node;
    if (node->data > val) return search(node->lchild, val);
    return search(node->rchild, val);
}

Node *insert(Node *node, int val) {
    if (node == NULL) return init(val);
    if (node->data == val) return node;
    if (node->data > val) node->lchild = insert(node->lchild, val); 
    else node->rchild = insert(node->rchild, val); 
    return node;
}

Node *find_pre(Node *node) {
    Node *temp = node->lchild;
    while (temp && temp->rchild) temp = temp->rchild;
    return temp;
}

Node *erase(Node *node, int val) {
    if (node == NULL) return node;
    if (node->data > val) node->lchild = erase(node->lchild, val);
    else if (node->data < val) node->rchild = erase(node->rchild, val);
    else {
        if (node->lchild == NULL || node->rchild == NULL) {
            Node *temp = node->lchild ? node->lchild : node->rchild;
            free(node);
            return temp;
        } else {
            Node *temp = find_pre(node);
            node->data = temp->data;
            node->lchild = erase(node->lchild, temp->data);
        }

    }
    return node;
}

void output(Node *node) {
    if (node == NULL) return ;
    output(node->lchild);
    printf("%d ", node->data);
    output(node->rchild);
    return ;
}

void clear(Node *node) {
    if (node == NULL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
    return ;
}

int main() {
    Node *node = NULL;
    int op, val;
    while (~scanf("%d%d", &op, &val)) {
        switch (op) {
            case 0:
                printf("insert %d into tree\n", val);
                node = insert(node, val);
                break;
            case 1:
                printf("delete %d from tree\n", val);
                node = erase(node, val);
                break;

        }
        output(node);
        printf("\n");
    }
    clear(node);
    return 0;
}
