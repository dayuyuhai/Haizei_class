/*************************************************************************
	> File Name: thread_pool.c
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Aug 2020 04:22:17 PM CST
 ************************************************************************/

#include"head.h"
#include"thread_pool.h"

int full_flag = 0, empty_flag = 0;

void *thread_run(void *arg) {
    pthread_detach(pthread_self());
    struct task_queue *taskQueue = (struct task_queue *)arg;
    while (1) {
        char *str = task_queue_pop(taskQueue);
        printf("<%ld> %s\n", pthread_self(), str);
    }
    for (int i = 0; i < taskQueue->total; i++) {
        free(taskQueue->data[i]);
    }
    free(taskQueue->data);
}

void task_queue_init(struct task_queue *taskQueue, int size) {
    memset(taskQueue, 0, sizeof(struct task_queue));
    taskQueue->data = (char **)calloc(size, sizeof(char *));
    taskQueue->size = size;
    taskQueue->total = taskQueue->tail = taskQueue->head = 0;
    pthread_mutex_init(&taskQueue->mutex, NULL);
    pthread_cond_init(&taskQueue->cond, NULL);
}

void task_queue_push(struct task_queue *taskQueue, char *str) {
    if (taskQueue->total > taskQueue->size) {
        perror("total bound");
        exit(1);
    }

    pthread_mutex_lock(&taskQueue->mutex);
    if (taskQueue->total == taskQueue->size) {
        DBG(YELLOW"<FULL WAIT>\n"NONE BLUE);
        full_flag = 1;
        pthread_cond_wait(&taskQueue->cond, &taskQueue->mutex);
    }

    taskQueue->data[taskQueue->tail] = (char *)calloc(512, sizeof(char));
    strcpy(taskQueue->data[taskQueue->tail++], str);
    
    DBG(GREEN"<PUSH>"NONE" : %s\n", taskQueue->data[taskQueue->tail - 1]);

    taskQueue->total += 1;
    if (taskQueue->tail == taskQueue->size) taskQueue->tail -= taskQueue->size;
    
    pthread_mutex_unlock(&taskQueue->mutex);

    if (empty_flag == 1) {
        DBG(BLUE"<EMPTY\n>"NONE);
        pthread_cond_signal(&taskQueue->cond);
        empty_flag = 0;
    }
}

char *task_queue_pop(struct task_queue *taskQueue) {
    pthread_mutex_lock(&taskQueue->mutex);
    if (taskQueue->total == 0) {
        DBG(BLUE"<EMPTY WAIT>\n"NONE);
        empty_flag = 1;
        pthread_cond_wait(&taskQueue->cond, &taskQueue->mutex);
    }

    static char tmp[512];
    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, taskQueue->data[taskQueue->head]);
    taskQueue->head++;
    if (taskQueue->head == taskQueue->size) taskQueue->head -= taskQueue->size;
    taskQueue->total -= 1;
    DBG(RED"<POP>"NONE" : %s\n", taskQueue->data[taskQueue->tail - 1]);

    pthread_mutex_unlock(&taskQueue->mutex);

    if (full_flag == 1) {
        DBG(YELLOW"<FULL SIGNAL>\n"NONE);
        pthread_cond_signal(&taskQueue->cond);
        full_flag = 0;
    } 
    return tmp;
}
 
