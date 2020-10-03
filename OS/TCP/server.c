/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Sat 19 Sep 2020 09:24:27 PM CST
 ************************************************************************/

#include "head.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage : %s port!\n", argv[0]);
        exit(1);
    }
    int server_listen, port, fd;
    pid_t pid;
    port = atoi(argv[1]);
    if ((server_listen = socket_create(port)) < 0) {
        perror("socket_create");
        exit(1);
    }
    while (1) {
        if ((fd = accept(server_listen, NULL, NULL)) < 0) {
            perror("Accept");
            exit(1);
        }

        if ((pid = fork()) < 0) {
            perror("Accept");
            exit(1);
        }
        if (pid == 0) {
            close(server_listen);
            recv_file(fd);
            exit(0);
        } else {
            close(fd);
        }
    }
    return 0;
}
