/*************************************************************************
	> File Name: 3.one_thread_reactor.c
	> Author: 
	> Mail: 
	> Created Time: Wed 12 Aug 2020 04:10:09 PM CST
 ************************************************************************/

#include "head.h"
#include "common.h"
#define MAX 10
#define MAX_USR 1024

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s port!\n", argv[0]);
        exit(1);
    }
    int server_listen, sockfd, port, epollfd;
    int fd[MAX_USR];
    memset(fd, -1, sizeof(fd) * MAX_USR);
    port = atoi(argv[1]);
    if ((server_listen = socket_create(port)) < 0) {
        perror("server_create()");
        exit(1);
    }

    if ((epollfd = epoll_create(1)) < 0) {
        perror("epoll_create()");
        exit(1);
    } 


    struct epoll_event ev, events[MAX];

    ev.data.fd = server_listen;
    ev.events = EPOLLIN;

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, server_listen, &ev) < 0) {
        perror("epoll_ctl()");
        exit(1);
    }

    while (1) {
        int nfds = epoll_wait(epollfd, events, MAX, -1);
        if (nfds < 0) {
            perror("epoll_wait()");
            exit(1);
        }



        for (int i = 0; i < nfds; i++) {
            if (events[i].data.fd == server_listen && (events[i].events & EPOLLIN)) {
                if ((sockfd = accept(server_listen, NULL, NULL)) < 0) {
                    perror("accept()");
                    exit(1);
                }
                fd[sockfd] = sockfd;
                ev.events = EPOLLIN;
                ev.data.fd = sockfd;
                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, sockfd, &ev) < 0) {
                    perror("epoll_ctl()");
                    exit(1);
                }
            } else {
                if (events[i].events & EPOLLIN) {
                    char buff[1024];
                    recv(ev.data.fd, buff, sizeof(buff), 0);
                    printf("recv %s\n", buff);
                }
            }
        }
    }

    return 0;
}
