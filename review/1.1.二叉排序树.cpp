/*************************************************************************
	> File Name: 1.1.二叉排序树.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 26 Jan 2021 08:41:01 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define KEY(a) (n ? n->key : 0)

typedef struct Node {
    int key;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = val;
    node->lchild = node->rchild = NULL;
    return node;
}

int search(Node *root, int val) {
    if (root == NULL) return 0;
    if (root->key == val) return 1;
    if (root->key > val) return search(root->lchild, val);
    return search(root->rchild, val);
}

Node *insert(Node *root, int val) {
    if (root == NULL) return NULL;
    if (root->key == val) return root;
    if (root->key > val) root->lchild = insert(root->lchild, val);
    else root->rchild = insert(root->rchild, val);
}

Node *erase(Node *root, int val) {
    if (root == NULL) return NULL:
    if (root->key > val) {
        root->lchild = erase(root->lchild, val);
    } else if (root->key < val) {
        root->rchild = erase(root->rchild, val);
    } else {
        if (root->lchild == NULL || root->rchild == NULL) {
            Node *temp = (root->lchild) ? root->lchild : root->rchild;
            return temp;
        } else {
            Node *temp = get_pre(root);
            root->key = temp->key;
            erase(root->lchild, val);
        }
    }
}

void output(Node *root) {
    if (root == NULL) return ;
    output(root->lchild);
    printf("(%d %d %d)\n", KEY(root), KEY(root->lchlid), KEY(root->rchild));
    output(root->rchild);
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
}

int main() {

    return 0;
}
