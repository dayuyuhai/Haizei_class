/*************************************************************************
	> File Name: 1.server.c
	> Author: 
	> Mail: 
	> Created Time: Sun 09 Aug 2020 04:12:12 PM CST
 ************************************************************************/

#include "head.h"
#include "common.h"

struct TASK_N_FD {
    struct task_queue *taskQueue;
    int fd;
}

void *do_chat(void *arg) {
    pthread_detach(pthread_self());
    struct TASK_N_FD task_n_fd = *(struct TASK_N_FD *)arg;
    char name[50] = {0};
    char ip[20] = {0};
    struct sockaddr_in client;
    bzero(&client, sizeof(client));
    socklen_t len  = sizeof(client);
    getpeername(task_n_fd.fd, (struct sockaddr *)&client, &len);
    strcpy(ip, inet_ntoa(client.sin_addr));

    while (1) {
        ssize_t nrecv;
        char buff[512] = {0};
        if ((nrecv = recv(fd, buff, sizeof(buff), 0)) <= 0) {
            close(fd);
            return NULL;
        }
        task_queue_push(&(task_n_fd.taskQueue), buff);
        printf("Recv ; %s\n", buff);
        send(fd, buff, strlen(buff), 0);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s port!\n", argv[0]);
        exit(1);
    }
    int listener, port;
    port = atoi(argv[1]);
    if ((listener = socket_create(port)) < 0) {
        perror("socket_create()");
        exit(1);
    }
    while (1) {
        int newfd;
        if ((newfd = accept(listener, NULL, NULL)) < 0) {
            perror("accept()");
            exit(1);
        }
        struct TASK_N_FD task_n_fd;
        task_queue_init(&(task_n_fd.taskQueue), SIZE);
        pthread_t tid[THREADNUM];

        for (int i = 0; i < THREADNUM; i++) {
            pthread_create(&tid[i], NULL, do_char, (void *)&task_n_fd);
        }
    }


    return 0;
}
