/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Wed 19 Aug 2020 02:22:38 PM CST
 ************************************************************************/

#include "head.h"
char *conf = "./chat.conf";
int epollfd;
struct User *users;
int maxfd = 0;
int cnt_online = 0;

int main(int argc, char **argv) {
    int opt, port = 0, server_listen, epollfd, sockfd;
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
            case 'p':
                port = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage : %s -p port!\n", argv[0]);
                exit(1);
        }
    }

    if (!port) port = atoi(get_conf(conf, "PORT"));

    if ((server_listen = socket_create(port)) < 0) {
        perror("socket_create()");
        exit(1);
    }

    make_non_block(server_listen);
    DBG(GREEN"INFO"NONE" : server started on port %d\n", port);

    users = (struct User *)calloc(MAXUSER, sizeof(struct User));

    DBG(GREEN"INFO"NONE" : calloced memory for storing users\n");

    if ((epollfd = epoll_create(1)) < 0) {
        perror("epoll_create()");
        exit(1);
    }

    maxfd = server_listen;
    DBG(GREEN"INFO"NONE" : main reactor created\n");

    struct task_queue taskQueue;
    task_queue_init(&taskQueue, MAXUSER, epollfd);

    DBG(GREEN"INFO"NONE" : taskQueue created and init\n");

    pthread_t *tid = (pthread_t *) calloc(THREADNUM, sizeof(pthread_t));
    for (int i = 0; i < THREADNUM; i++) {
        pthread_create(&tid[i], NULL, thread_run, (void *)&taskQueue);
    }

    DBG(GREEN"INFO"NONE" : Thread poll created for worker\n");

    users[0].fd = server_listen;
    strcpy(users[0].name, "server_listen");
    strcpy(users[0].real_name, "server_listen");

    add_event(epollfd, server_listen, EPOLLIN, &users[0]);

    pthread_t heart_t;
    pthread_create(&heart_t, NULL, heart_beat, NULL);

    struct epoll_event events[MAXEVENTS];

    while (1) {
        int nfds = epoll_wait(epollfd, events, MAXEVENTS, -1);
        if (nfds < 0) {
            perror("epoll_wait()");
            exit(1);
            // 正常要判断出错信号类型，直接推出不友好
        }
        for (int i = 0; i < nfds; i++) {
            struct User *user = (struct User *)events[i].data.ptr;
            if (user->fd == server_listen && (events[i].events & EPOLLIN)) {
                if ((sockfd = accept(server_listen, NULL, NULL)) < 0) {
                    perror("accept()");
                    exit(1);
                }
                make_non_block(sockfd);
                
                if (sockfd > maxfd) maxfd = sockfd;
                DBG(YELLOW"Acceptor"NONE" : Accept a new client\n");
                struct User newuser;
                memset(&newuser, 0, sizeof(newuser));
                newuser.fd = sockfd;
                newuser.online = 2;
                newuser.flag = 10;
                strcpy(newuser.name, "New Client");
                int sub = find_sub(users, MAXUSER);
                if (sub < 0) {
                    DBG(YELLOW"Warning"NONE" : Too many clients\n");
                }
                users[sub] = newuser;
                add_event(epollfd, sockfd, EPOLLIN | EPOLLET, &users[sub]);
                // task_queue_push(&taskQueue, &users[sub]);
            }
            else {
                if (events[i].events & EPOLLIN) {
                    task_queue_push(&taskQueue, user);
                }
            }
        }
    }

    return 0;
}
