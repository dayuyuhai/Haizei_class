/*************************************************************************
	> File Name: 5.level.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sat 27 Jun 2020 05:51:33 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node {
    char data;
    struct Node *lchild, *rchild;
} Node;

typedef struct Tree {
    Node *root;
    int n;
} Tree;

typedef struct Stack {
    Node **data;
    int top;
    int size;
} Stack;

typedef struct Queue {
    Node **data;
    int head, tail, size, cnt;
} Queue;

Node *getNewNode(char val) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = val;
    p->lchild = p->rchild = NULL;
    return p;
}

Tree *getNewTree() {
    Tree *p = (Tree *)malloc(sizeof(Tree));
    p->root = NULL;
    p->n = 0;
    return p;
}

Stack *init(int n) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    s->data = (Node **)malloc(sizeof(Node *) * n);
    s->top = -1;
    s->size = n;
    return s;
}

Node *front(Queue *q) {
    return q->data[q->head];
}

int empty_q(Queue *q) {
    return q->cnt == 0;
}

int push_q(Queue *q, Node *data) {
    if (q == NULL) return 0;
    if (q->cnt == q->size) return 0;
    q->data[q->tail++] = data;
    q->cnt += 1;
    if (q->tail == q->size) q->tail -= q->size;
    return 1;
}

int pop_q(Queue *q) {
    if (q == NULL) return 0;
    if (empty_q(q)) return 0;
    q->head++;
    if (q->head == q->size) q->head -= q->size;
    q->cnt -= 1;
    return 1;
}

Queue *init_q(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (Node **)malloc(sizeof(Node *) * 2 * n);
    q->head = q->tail = q->cnt = 0;
    q->size = 2 * n;
    return q;
}

int empty(Stack *s) {
    return s->top == -1;
}

int push(Stack *s, Node *val) {
    if (s == NULL) return 0;
    if (s->size == s->top + 1) return 0;
    s->data[++s->top] = val;
    return 1;
}
    
int pop(Stack *s) {
    if (s == NULL) return 0;
    if (empty(s)) return 0;
    s->top--;
    return 1;
}

Node *top(Stack *s) {
    return s->data[s->top];
}


void clear_q(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

void clear(Node *p) {
    if (p == NULL) return ;
    clear(p->lchild);
    clear(p->rchild);
    free(p);
    return ;
}

void clear_tree(Tree *p) {
    if (p == NULL) return ;
    clear(p->root);
    free(p);
    return ;
}

void clear_stack(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

void level_order(Tree *tree) {
    Queue *q = init_q(tree->n);
    push_q(q, tree->root);
    for (int i = 0; i < tree->n; i++) {
		i && printf(" ");
        printf("%c", front(q)->data);
		Node *temp = front(q);
        if (temp->lchild != NULL) push_q(q, temp->lchild);
        if (temp->rchild != NULL) push_q(q, temp->rchild);
        pop_q(q);
    }
	printf("\n");
    clear_q(q);
    return ;
}

Node *build(const char *str, int *cnt) {
    Stack *s = init(strlen(str));
    Node *temp = NULL, *p = NULL;
    int flag = 0;
	*cnt = 0;
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
                if (!empty(s) && flag) top(s)->rchild = temp;
                if (!empty(s) && !flag) top(s)->lchild = temp;
                ++(*cnt);
                break;
        }
        ++str;
    }
    clear_stack(s);
    if (temp && !p) p = temp;
    return p;
}

int main() {
    char str[1000];
    scanf("%[^\n]", str);
    int cnt;
    Tree *tree = getNewTree();
    tree->root = build(str, &cnt);
    tree->n = cnt;
    level_order(tree);
    clear_tree(tree);
    return 0;
}
