/*************************************************************************
	> File Name: 3-3.one_thread_reactor.c
	> Author: 
	> Mail: 
	> Created Time: Fri 14 Aug 2020 07:55:06 PM CST
 ************************************************************************/

#include "head.h"
#include "./thread_pool/thread_pool.h"
#include "./usr/user.h"
#include "common.h"
#define MAXTHREAD 10
#define MAXQUEUE 20
#define MAXEVENTS 10

#define FAIL_LOGIN "You are already in our chat room . -_-"
#define SUCCESS_LOGIN "Welcome to the chat room ! ^^"

int epollfd;
struct User user[MAXUSER];

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s port!\n", argv[0]);
        exit(1);
    }
    int server_listen, sockfd, port;
    int fd[MAXUSER] = {0};
    port = atoi(argv[1]);
    if ((server_listen = socket_create(port)) < 0) {
        perror("socket_create()");
        exit(1);
    }

    memset(user, 0, sizeof(user));

    struct task_queue taskQueue;
    task_queue_init(&taskQueue, MAXQUEUE);

    pthread_t *tid = (pthread_t *)calloc(MAXTHREAD, sizeof(pthread_t));

    for (int i = 0; i < MAXTHREAD; i++) {
        pthread_create(&tid[i], NULL, thread_run, (void *)&taskQueue);
    }

    pthread_t h_tid;
    pthread_create(&h_tid, NULL, thread_heart, NULL);

    if ((epollfd = epoll_create(1)) < 0) {
        perror("epoll_create()");
        exit(1);
    }

    struct epoll_event ev, events[MAXEVENTS];

    ev.data.fd = server_listen;
    ev.events = EPOLLIN | EPOLLET;

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, server_listen, &ev) < 0) {
        perror("epoll_ctl()");
        exit(1);
    }

    // signal(SIGINT, server_logout);

    
    while (1) {
        int nfds = epoll_wait(epollfd, events, MAXEVENTS, -1);
        if (nfds < 0) {
            perror("epoll_wait");
            exit(1);
        }
        DBG(YELLOW"<Debg>"NONE" : After wait nfds = %d\n", nfds);
        for (int i = 0; i < nfds; ++i) {
            if (events[i].data.fd == server_listen  && (events[i].events & EPOLLIN)) {
                if ((sockfd = accept(server_listen, NULL, NULL)) < 0) {
                    perror("accept()");
                    exit(1);
                }
                struct ChatMsg c_syn;
                memset(&c_syn, 0, sizeof(c_syn));
                recv(sockfd, &c_syn, sizeof(c_syn), 0);
                if ((find_name(c_syn.name) == -1) && (c_syn.type & CHAT_SYN != 0)) {
                    c_syn.type |= CHAT_ACK;
                    strcpy(c_syn.msg, SUCCESS_LOGIN);
                    DBG(BLUE"server : recv"NONE" login req\n");
                    send(sockfd, &c_syn, sizeof(c_syn), 0);
                } else {
                    c_syn.type |= CHAT_NAK;
                    strcpy(c_syn.msg, FAIL_LOGIN);
                    send(sockfd, &c_syn, sizeof(c_syn), 0);
                }
                strcpy(user[sockfd].name, c_syn.name);
                user[sockfd].online = 1;
                user[sockfd].fd = sockfd;
                user[sockfd].flag = 3;
                printf("user fd = %d\n", sockfd);


                fd[sockfd] = sockfd;
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = sockfd;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) < 0) {
                    perror("epoll_ctl()");
                    exit(1);
                }
            } else {
                if (events[i].events & EPOLLIN) {
                    task_queue_push(&taskQueue, events[i].data.fd);
                }
            }
        }
    }
    return 0;
}
