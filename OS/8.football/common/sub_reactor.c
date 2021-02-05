/*************************************************************************
	> File Name: sub_reactor.c
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年10月21日 星期三 20时29分57秒
 ************************************************************************/

#include "head.h"
#include "thread_pool.h"
#include "sub_reactor.h"
#define MAX 50

void *sub_reactor(void *arg){
    //NTHREAD 线程数量小于cpu核心
    struct task_queue *taskQueue = (struct task_queue *)arg;
    pthread_t *tid = (pthread_t *)calloc(NTHREAD, sizeof(pthread_t));
    for (int i = 0; i < NTHREAD; i++) {
        pthread_create(&tid[i], NULL, thread_run, (void *)taskQueue);
    }
    struct epoll_event ev, events[MAX];
    sigset_t mask, orig_mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);
    while (1) {
        DBG(RED"Sub Reactor"NONE" ; Epoll Waiting...\n");
        pthread_sigmask(SIG_SETMASK, &mask, &orig_mask);
        int nfds = epoll_wait(taskQueue->epollfd, events, MAX, -1);
        pthread_sigmask(SIG_SETMASK, &orig_mask, NULL);
        if (nfds < 0) {
            perror("main : epoll_wait()");
            exit(1);
        }
        for (int i = 0; i < nfds; i++) {
            struct User *user = (struct User *)events[i].data.ptr;
            DBG(L_YELLOW"events[n].data.ptr->name = %s \n"NONE, user->name);
            if (events[i].events & EPOLLIN) {
                task_queue_push(taskQueue, (struct User *)events[i].data.ptr);
            }
        }
    }
    return NULL;
}
