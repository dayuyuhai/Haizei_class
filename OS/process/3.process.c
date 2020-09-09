/*************************************************************************
	> File Name: 3.process.c
	> Author: 
	> Mail: 
	> Created Time: Sat 01 Aug 2020 02:44:06 PM CST
 ************************************************************************/

#include<stdio.h>
#include"head.h"

int main() {
    pid_t pid;
    int x = 0;
    for (int i = 1; i <= 100; i++) {
        if ((pid = fork()) < 0) {
            perror("fork()");
            exit(1);
        }
        x = i;
        if (pid == 0) break;
    }
    if (pid == 0) printf("我是第%d个孩子！\n", x);
    else {
        for (int i = 1; i <= x; i++) {
            wait(NULL);
        }
    }
    return 0;
}
