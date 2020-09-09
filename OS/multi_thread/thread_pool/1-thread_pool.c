/********************************mZ****************************************
	> File Name: thread_pool.c
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Aug 2020 04:22:17 PM CST
 ************************************************************************/

#include"head.h"
#include"thread_pool.h"

void *thread_run(void *arg) {
    pthread_detach(pthread_self());
    struct task_queue *taskQueue = (struct task_queue *)arg;
    while (1) {
        char *str = task_queue_pop(taskQueue);
        printf("<%ld> %s\n", pthread_self(), str);
    }
}

void task_queue_init(struct task_queue *taskQueue, int size) {
    taskQueue->data = calloc(size, sizeof(void *));
    taskQueue->size = size;
    taskQueue->total = taskQueue->tail = taskQueue->head = 0;
    pthread_mutex_init(&taskQueue->mutex, NULL);
    pthread_cond_init(&taskQueue->cond, NULL);
}

void task_queue_push(struct task_queue *taskQueue, char *str) {
    pthread_mutex_lock(&taskQueue->mutex);
    if (taskQueue->total == taskQueue->size) {
        pthread_mutex_unlock(&taskQueue->mutex);
        DBG(YELLOW("full filled!\n"));
        return ;
    }

    taskQueue->data[taskQueue->tail] = str;

    taskQueue->total += 1;
    if (++taskQueue->tail == taskQueue->size) taskQueue->tail = 0;
    pthread_cond_signal(&taskQueue->cond);
    pthread_mutex_unlock(&taskQueue->mutex);
}

char *task_queue_pop(struct task_queue *taskQueue) {
    pthread_mutex_lock(&taskQueue->mutex);
    if (taskQueue->total == 0) {
        pthread_cond_wait(&taskQueue->cond, &taskQueue->mutex);
    }

    char *tmp = taskQueue->data[taskQueue->head];
    if (++taskQueue->head == taskQueue->size) taskQueue->head = 0;
    taskQueue->total -= 1;

    pthread_mutex_unlock(&taskQueue->mutex);

    return tmp;
}
 
