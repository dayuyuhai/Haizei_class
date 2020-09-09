/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Sun 09 Aug 2020 04:22:50 PM CST
 ************************************************************************/

#include "head.h"
#include "common.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage : %s ip port!\n", argv[0]);
        exit(1);
    }
    int sockfd, port;
    char ip[20] = {0};
    strcpy(ip, argv[1]);
    port = atoi(argv[2]);

    if ((sockfd = socket_connect(ip, port)) < 0) {
        perror("socket_connect");
        exit(1);
    }

    while (1) {
        char buff[512] = {0};
        scanf("%[^\n]s", buff);
        getchar();
        send(sockfd, buff, strlen(buff), 0);
        recv(sockfd, buff, strlen(buff), 0);
        printf("Server : %s\n", buff);
    }





    return 0;
}
