/*************************************************************************
	> File Name: 1.thread.c
	> Author: 
	> Mail: 
	> Created Time: Sat 01 Aug 2020 06:19:28 PM CST
 ************************************************************************/

#include<stdio.h>
#include"head.h"

void *print(void *arg) {
    printf("我是 %d 子线程！\n", *(int *)arg);
}

int main(int argc, char **argv) {
    int tmp_arg[100] = {0};
    pthread_t tid[100];
    for (int i = 1; i < 100; i++) {
        tmp_arg[i] = i;
        pthread_create(&tid[i], NULL, print, (void *)&tmp_arg[i]);
    }
    for (int i = 0; i < 100; i++) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}
