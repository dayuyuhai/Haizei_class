/*************************************************************************
	> File Name: 1.server.c
	> Author: 
	> Mail: 
	> Created Time: Sun 09 Aug 2020 04:12:12 PM CST
 ************************************************************************/

#include "head.h"
#include "common.h"

void *do_chat(void *arg) {
    int fd = *(int *)arg;
    // 解锁
    char name[50] = {0};
    char ip[20] = {0};
    struct sockaddr_in client;
    bzero(&client, sizeof(client));
    socklen_t len  = sizeof(client);
    getpeername(fd, (struct sockaddr *)&client, &len);
    strcpy(ip, inet_ntoa(client.sin_addr));

    while (1) {
        ssize_t nrecv;
        char buff[512] = {0};
        if ((nrecv = recv(fd, buff, sizeof(buff), 0)) <= 0) {
            close(fd);
            return NULL;
        }
        printf("Recv : %s\n", buff);
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
        pthread_t tid;
        int newfd;
        // 可以枷锁
        if ((newfd = accept(listener, NULL, NULL)) < 0) {
            perror("accept()");
            exit(1);
        }
        pthread_create(&tid, NULL, do_chat, (void *)&newfd);
        usleep(50);  // 这么写有风险
    }


    return 0;
}
