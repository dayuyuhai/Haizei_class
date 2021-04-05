/*************************************************************************
	> File Name: 1.二叉排序树.cpp
	> Author: 
	> Mail: 
	> Created Time: Thu 11 Mar 2021 08:56:18 AM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define KEY(n) (n ? n->key : 0)
#define MAX(a, b) (a > b ? a : b) 
#define SIZE(n) (n ? n->size : 0)   // 此处的size代表height
#define L(n) (n ? n->lchild : NULL)
#define R(n) (n ? n->rchild : NULL)


typedef struct Node {
    int key, size;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->size = 1;
    node->lchild = node->rchild = NULL;
    return node;
}

void Update(Node *root) {
    root->size = MAX(SIZE(L(root)), SIZE(R(root))) + 1;
}

Node *pre(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp;
}

int search(Node *root, int key) {
    if (root == NULL) return 0;
    if (root->key == key) return 1;
    if (root->key > key) return search(root->lchild, key);
    return search(root->rchild, key);
}

int search_k(Node *root, int k) {
    if (root == NULL) return -1;
    if (SIZE(L(root)) == k - 1) return KEY(root);
    if (SIZE(L(root)) > k - 1) return search_k(root->lchild, k);
    return search_k(root->rchild, k - SIZE(L(root)) - 1);
}

Node *insert(Node *root, int key) {
    if (root == NULL) return getNewNode(key);
    if (root->key == key) return root;
    if (root->key > key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    Update(root);
    return root;
}

Node *erase(Node *root, int key) {
    if (root == NULL) return NULL;
    if (root->key > key) root->lchild = erase(root->lchild, key);
    else if (root->key < key) root->rchild = erase(root->rchild, key);
    else {
        if (root->lchild == NULL || root->rchild == NULL) {
            Node *temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return temp;
        } else {
            Node *temp = pre(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
    }
    Update(root);
    return root;
}

void print(Node *root) {
    printf("%d[%d] (%d, %d)\n", 
          KEY(root), SIZE(root), KEY(L(root)), KEY(R(root)));
}

void output(Node *root) {
    if (root == NULL) return ;
    print(root);
    output(root->lchild);
    output(root->rchild);
    return ;
}

void output_k(Node *root, int k) {
    if (k == 0 || root == NULL) return ;
    if (SIZE(L(root)) > k - 1) output_k(root->lchild, k);
    else {
        output(root->lchild);
        print(root);
        output_k(root->rchild, k - SIZE(L(root)) - 1);
    }
    return ;
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

int main() {
    int op, val, k;
    Node *root = NULL;
    while (~scanf("%d %d %d", &op, &val, &k)) {
        switch (op) {
            case 0: printf("search %d, result : %d\n", val, search(root, val)); break;
            case 1: printf("search_k %d, result : %d\n", k, search_k(root, k)); break;
            case 2: root = insert(root, val); break;
            case 3: root = erase(root, val); break;
            case 4: output_k(root, k);
        }
        if (op == 2 || op == 3) {
            output(root);
            printf("------------\n");
        }
    }
    return 0;
}
