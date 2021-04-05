/*************************************************************************
	> File Name: ztest.cpp
	> Author: 
	> Mail: 
	> Created Time: Sun 21 Mar 2021 05:33:53 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ztest.h>
#include<linknode.h>

struct TestFunc func_head, *func_tail = &func_head;

int cnt = 0, cnt_suc = 0;

int RUN_ALL_TESTS() {
    for (struct LinkNode *p = func_head.p.next; p; p = p->next) {
        struct TestFunc *flink = Head(struct TestFunc, p);
        cnt = cnt_suc = 0;
        printf(GREEN("[====RUN====] ") RED("%s") "\n", flink->fname);
        flink->func();

        printf(GREEN("["));
        double rate = 100.0 * cnt_suc / cnt;
        if (cnt == cnt_suc) printf(BLUE("%8.2lf%%"), rate);
        else printf(RED("%8.2lf%%"), rate);
        printf(GREEN("  ]") " total : %d success : %d\n\n", cnt, cnt_suc);
    }
}

void add_func(void (*func)(), const char *name) {
    struct TestFunc *temp = (struct TestFunc *)calloc(1, sizeof(struct TestFunc));
    func_tail->p.next = &(temp->p);
    temp->func = func;
    temp->fname = name;
    func_tail = temp;
}
