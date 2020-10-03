/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: Sat 19 Sep 2020 09:08:13 PM CST
 ************************************************************************/
#include "head.h"

int main(int argc, char **argv) {
    int port, sockfd;
    char name[1024] = {0};

    if (argc != 4) {
        fprintf(stderr, "Usage : %s ip port path_of_file!\n", argv[0]);
        exit(1);
    }

    port = atoi(argv[2]);
    strcpy(name, argv[3]);

    if ((sockfd = socket_connect(argv[1], port)) < 0) {
        perror("socket_connect()");
        return 1;
    }

    send_file(name, sockfd);
    
    close(sockfd);

    return 0;
}

