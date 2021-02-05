/*************************************************************************
	> File Name: 1.二叉排序树.cpp
	> Author: 
	> Mail: 
	> Created Time: Fri 22 Jan 2021 07:21:20 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

#define KEY(n) (n ? n->key : 0)
#define SIZE(n) (n ? n->size : 0)

typedef struct Node {
    int key, size;
    struct Node *lchild, *rchild;
} Node;

void Upgrade(Node *root) {
   root->size = SIZE(root->lchild) + SIZE(root->rchild) + 1;
}

Node *pre(Node *root) {
    root = root->lchild;
    while (root->rchild) root = root->rchild;
    return root;
}

Node *getNewNode(int key) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->lchild = node->rchild = NULL;
    return node;
}

int search(Node *root, int val) {
    if (root == NULL) return 0;
    if (root->key == val) return 1;
    if (val < root->key) return search(root->lchild, val);
    return search(root->rchild, val);
}

int search_k(Node *root, int k) {
    if (root == NULL) return -1;
    if (SIZE(root->lchild) + 1 == k) return root->key;
    if (root->size > k) return search_k(root->lchild, k);
    return search_k(root->rchild, k);
}

Node *insert(Node *root, int val) {
    if (root == NULL) return getNewNode(val);
    if (root->key == val) return root;
    if (root->key > val) root->lchild = insert(root->lchild, val);
    else root->rchild = insert(root->rchild, val);
    Upgrade(root);
    return root;
}

Node *erase(Node *root, int val) {
    if (root == NULL) return NULL;
    if (root->key > val) {
        root->lchild = erase(root->lchild, val);
    } else if (root->key < val) {
        root->rchild = erase(root->rchild, val);
    } else {
        /*
        if (root->lchild == NULL && root->rchild == NULL) {
            free(root);
            return NULL;
        } else 
        */
        if (root->lchild == NULL || root->rchild == NULL) {
            Node *temp = (root->lchild) ? root->lchild : root->rchild;
            free(root);
            return temp;
        } else {
            Node *temp = pre(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
    }
    Upgrade(root);
} 

void output(Node *root) {
    if (root == NULL) return ;
    output(root->lchild);
    printf("(%d %d %d)\n", KEY(root), KEY(root->lchild), KEY(root->rchild));
    output(root->rchild);
}

void output_k(Node *root, int k) {
    if (root == NULL) return ;
    if (root->size == k) {
        output(root->lchild);
        printf("%d\n", root->key);
    } else if (root->size > k) output_k(root->lchild, k);
    else output_k(root->rchild, k);
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
}

int main() {
    int op, val, k;
    Node *root = NULL;
    while (~scanf("%d %d", &op, &val)) {
        switch (op) {
            case 0: printf("search %d %s\n", val, search(root, val) ? "suc" : "fai"); break;
            case 1: root = insert(root, val); break;
            case 2: root = erase(root, val); break;
            case 3: {
                scanf("%d", &k);
                printf("search_k %d is %d\n", k, search_k(root, k));
            } break;
            case 4: {
                output(root);
                printf("----------------\n");
            } break;
            case 5: {
                scanf("%d", &k);
                output_k(root, k);
                printf("----------------\n");
            }

        }
        /*
        if (op) {
            output(root);
            printf("----------------\n");
        }
        */
    }
    return 0;
}
