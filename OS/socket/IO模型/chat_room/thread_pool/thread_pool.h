/*************************************************************************
	> File Name: thread_pool.h
	> Author: 
	> Mail: 
	> Created Time: Fri 14 Aug 2020 04:58:05 PM CST
 ************************************************************************/

#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H

typedef int TYPE;

/*
typedef union thread_pool_data {
    char    char_data;
    int     int_data;
    uint32_t u32_data;
    uint64_t u64_data;
    char *  char_pdata;
    int * int_pdata;
} thread_pool_data_t;
*/


struct task_queue{
    int size;
    int total;
    int head;
    int tail;
    TYPE  *fd;
    // thread_pool_data_t data;      
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

int find_name(char *name);

void task_queue_init(struct task_queue *taskQueue, int size);
void task_queue_push(struct task_queue *taskQueue, int fd);
int task_queue_pop(struct task_queue *taskQueue);
void *thread_run(void *arg);
void *thread_heart(void *arg);
#endif
