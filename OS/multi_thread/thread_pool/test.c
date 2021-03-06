/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Aug 2020 04:28:24 PM CST
 ************************************************************************/

#include"thread_pool.h"
#include"head.h"
#define SIZE 50
#define THREADNUM 5
#define BUFFSIZE 512

int main() {
    struct task_queue taskQueue;
    task_queue_init(&taskQueue, SIZE);
    pthread_t tid[THREADNUM];

    for (int i = 0; i < THREADNUM; i++) {
        pthread_create(&tid[i], NULL, thread_run, (void *)&taskQueue);
    }

    char buff[SIZE][BUFFSIZE] = {0};

    int sub = 0;

    char buf[512] = {0};

    while (1) {
        scanf("%s", buf);
        task_queue_push(&taskQueue, buf);
        memset(buf, 0, sizeof(buf));
        /*
        FILE *fp = fopen("./thread_pool.c", "r");
        if (fp == NULL) {
            perror("fopen()");
            exit(1);
        }
        while (fgets(buff[sub], sizeof(buff), fp) != NULL) {
            task_queue_push(&taskQueue, buff[sub]);
            if (++sub >= SIZE) sub = 0;
        }
        fclose(fp);
        */
    }
    return 0;
}
