/*************************************************************************
	> File Name: 21.binary_search_tree.cpp
	> Author: 
	> Mail: 
	> Created Time: Sat 19 Dec 2020 09:58:02 AM CST
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#define KEY(n) (n ? n->key : 0)
#define SIZE(n) (n ? n->size : 0)
#define L(n) (n ? n->lchild : NULL)

typedef struct Node {
    int key, size;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int key) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->lchild = p->rchild = NULL;
    return p;
}

int search(Node *root, int val) {
    if (root == NULL) return 0;
    if (root->key == val) return 1;
    if (val < root->key) return search(root->lchild, val);
    return search(root->rchild, val);
}

    int *search_k(Node *root, int k) {
        if (root == NULL) return -1;
    if (SIZE(L(root)) - 1 == k) return root;
    if (k <= SIZE(L(root))) {
        return search_k(root->lchild, k);
    }
    return search_k(root->rchild, k - SIZE(L(root)) - 1);
}

void update_size(Node *root) {
    root->size = SIZE(root->lchild) + SIZE(root->rchild) + 1;
    return ;
}


Node *insert(Node *root, int key) {
    if (root == NULL) return getNewNode(key);
    if (root->key == key) return root;
    if (key < root->key) root->lchild = insert(root->lchild, key);
    else root->rchild = insert(root->rchild, key);
    update_size(root);
    return root;
}


Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild) temp = temp->rchild;
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NULL) return NULL;
    if (key < root->key) {
        root->lchild = erase(root->lchild, key);
    } else if (key > root->key) {
        root->rchild = erase(root->rchild, key);
    } else {
        // 度为1情况的代码也能解决度为0的情况，所以第一个if可以去掉
        
        //if (root->lchild == NULL && root->rchild == NULL) {
          //  free(root);
            //return NULL;
        // } else if
        if (root->lchild == NULL || root->rchild == NULL) {
            Node *temp = root->lchild ? root->lchild : root->rchild;
            free(root);
            return temp;
        } else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
    }
    update_size(root);
    return root;
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

void output(Node *root) {
    if (root == NULL) return ;
    output(root->lchild);
    printf("(%d, %d, %d)\n", KEY(root), KEY(root->lchild), KEY(root->rchild));
    output(root->rchild);
    return ;
}

void output_k(Node *root, int k) {
    if (k == 0 || root == NULL) return ;
    if (k <= SIZE(L(root)) + 1) {
        output_k(root->lchild, k);
    } else {
        output_k(root->lchild);
        print(root);
        output_k(root->rchild, k - SIZE(L(root)) - 1);
        
    }
    return ;
}

int main() {
    int op, val;
    Node *root =  NULL;
    while (~scanf("%d%d", &op, &val)) {
        switch (op) {
            case 0: printf("search %d, result : %d\n", val, search(root, val)); break;
            case 1: root = insert(root, val); break;
            case 2: root = erase(root, val); break;
        }
        if (op) {
            output(root);
            printf("------------\n");
        }
    }
    return 0;
}
