/*************************************************************************
	> File Name: thread_pool.h
	> Author: suyelu 
	> Mail: suyelu@126.com
	> Created Time: Tue 04 Aug 2020 04:16:34 PM CST
 ************************************************************************/

#ifndef _THREAD_POOL_H
#define _THREAD_POOL_H
#include "head.h"
struct task_queue{
	int sum;
	int epollfd;
	struct User **team;
	int head;
	int tail;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};

void task_queue_init(struct task_queue *taskQueue, int sum, int epollfd);
void task_queue_push(struct task_queue *taskQueue, struct User *user);
struct User *task_queue_pop(struct task_queue *taskQueue);
void *thread_run(void *arg);

#define MAXTASK 100
#define NTHREAD 8 
#endif
