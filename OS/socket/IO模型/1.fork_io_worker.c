/*************************************************************************
	> File Name: 0.one_thread.c
	> Author: 
	> Mail: 
	> Created Time: Wed 12 Aug 2020 02:37:28 PM CST
 ************************************************************************/

#include"head.h"
#include"common.h"

void worker(int fd) {
    while (1) {
        char buff[512] = {0};
        if ((recv(fd, buff, sizeof(buff), 0)) <= 0) {
            break;
        }
        printf("%s\n", buff);
    }
    close(fd);
    DBG("Logout!\n")
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s port!\n", argv[0]);
        exit(1);
    }

    int sockfd, port, server_listen;
    port = atoi(argv[1]);
    if ((server_listen = socket_create(port)) < 0) {
        perror("socket_create()");
        exit(1);
    }

    pid_t pid;

    while (1) {
        struct sockaddr_in client;
        socklen_t len = sizeof(client);
        char buff[512] = {0};
        if ((sockfd = accept(server_listen, (struct sockaddr *)&client, &len)) < 0) {
            perror("accept()");
            exit(1);
        }
        if ((pid = fork()) < 0) {
            perror("fork()");
            exit(1);
        }

        if (pid == 0) {
            worker(sockfd);
            exit(0);
        }

        read(sockfd, buff, sizeof(buff));
        printf("%s\n", buff);
        close(sockfd);
    }


    return 0;
}
