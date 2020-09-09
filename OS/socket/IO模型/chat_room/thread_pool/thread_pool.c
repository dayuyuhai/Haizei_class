/*************************************************************************
	> File Name: thread_pool.c
	> Author: 
	> Mail: 
	> Created Time: Fri 14 Aug 2020 04:56:33 PM CST
 ************************************************************************/

#include "head.h"
#include "thread_pool.h"
#include "../usr/user.h"

extern int epollfd; 
extern struct User user[MAXUSER];

int find_name(char *name) {
    for (int i = 0; i < MAXUSER; i++) {
        if (user[i].online == 0) continue;
        if (strcmp(user[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

/*
void server_logout(int signum) {
    printf("recv logout signal!\n");
    struct ChatMsg c_fin;
    memset(&c_fin, 0, sizeof(c_fin));
    c_fin.type |= CHAT_FIN;
    for (int i = 0; i < MAXUSER; i++) {
        if (user[i].online == 0) continue;
        send(user[i].fd, &c_fin, sizeof(c_fin), 0);
    }
}
*/

void deal_recv_message(struct ChatMsg *c_msg, int fd) {
    if (c_msg->type & CHAT_PUB) {
        DBG(BLUE"server recv type: "NONE"pub\n");
        printf("%s\n", c_msg->msg);
    } else if (c_msg->type & CHAT_PRI) {
        DBG(BLUE"server recv type: "NONE"pri\n");
        printf("%s\n", c_msg->msg);
    }
    if (c_msg->type & CHAT_FIN) {
        DBG("%s ask for quit\n", c_msg->name);
        c_msg->type |= CHAT_FIN_1;
        send(fd, &c_msg, sizeof(c_msg), 0);
        sleep(1);
        user[fd].online = 0;
        epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
        close(fd);
    }
    /*
    if (c_msg->type & CHAT_FIN_1) {
        printf("server logout\n");
        exit(0);
    }
    */
}

void do_work(int fd) {
    struct ChatMsg c_msg;
    memset(&c_msg, 0, sizeof(c_msg));
    int nrecv = recv(fd, &c_msg, sizeof(c_msg), 0) == sizeof(c_msg);

    printf("nrecv= %d\n", nrecv);
    user[fd].flag = 3;
    printf("%x\n", c_msg.type);
    deal_recv_message(&c_msg, fd);
}

void task_queue_init(struct task_queue *taskQueue, int size) {
    taskQueue->size = size;
    taskQueue->total = taskQueue->head = taskQueue->tail = 0;
    taskQueue->fd = calloc(size, sizeof(TYPE));
    taskQueue->fd = calloc(size, sizeof(int));
    pthread_mutex_init(&taskQueue->mutex, NULL);
    pthread_cond_init(&taskQueue->cond, NULL);
    return ;
}

void task_queue_push(struct task_queue *taskQueue, int fd) {
    pthread_mutex_lock(&taskQueue->mutex);
    if (taskQueue->total == taskQueue->size) {
        printf("%d %d\n", taskQueue->total, taskQueue->size);
        pthread_mutex_unlock(&taskQueue->mutex);
        DBG(YELLOW"<taskQueue>"NONE" : taskQueue is full!\n");
        return;
    }
    taskQueue->fd[taskQueue->tail] = fd;
    taskQueue->total++;
    DBG(GREEN"<Push>"NONE" : %d\n", fd);
    if (++taskQueue->tail == taskQueue->size) {
        DBG(RED"<taskQueue>"NONE" : End\n");
        taskQueue->tail = 0;
    }
    pthread_cond_signal(&taskQueue->cond);
    pthread_mutex_unlock(&taskQueue->mutex);
}

int task_queue_pop(struct task_queue *taskQueue) {
    pthread_mutex_lock(&taskQueue->mutex);
    while (taskQueue->total == 0) {
        DBG(PURPLE"<Debug>"NONE" : taskQueue is empty!\n ");
        pthread_cond_wait(&taskQueue->cond, &taskQueue->mutex);
    }
    int fd = taskQueue->fd[taskQueue->head];
    taskQueue->total--;
    DBG(BLUE"<taskQueue>"NONE" : pop %d!\n", fd);
    if (++taskQueue->head == taskQueue->size) {
        taskQueue->head = 0;
    }
   // sleep(1);
    pthread_mutex_unlock(&taskQueue->mutex);
    return fd;
}

void *thread_heart(void *arg) {
    struct ChatMsg c_heart;
    while (1) {
        for (int i = 0; i < 100; i++) {
            if (user[i].online == 0) continue;

            memset(&c_heart, 0, sizeof(c_heart));
            printf("send %s heart beat\n", user[i].name);
            c_heart.type |= CHAT_HEART;
            strcpy(c_heart.msg, "heart beat from server");
            if (send(user[i].fd, &c_heart, sizeof(c_heart), 0) <= 0) {
                perror("heart send");
                exit(1);
            }
            DBG(RED"server send message : "NONE"%s\n", c_heart.msg);

            if (user[i].flag == 0) {
                printf("%s is not there, kick him out.\n", user[i].name);
                user[i].online = 0;
                epoll_ctl(epollfd, EPOLL_CTL_DEL, user[i].fd, NULL);
                close(user[i].fd);
                continue;
            }

            user[i].flag--;

        }
        printf(YELLOW"after two second\n"NONE);
        sleep(2);
    }
}

void *thread_run(void *arg) {
    pthread_detach(pthread_self());
    struct task_queue *taskQueue = (struct task_queue *)arg;
    while (1) {
        int fd = task_queue_pop(taskQueue);
        do_work(fd);
    }
}
