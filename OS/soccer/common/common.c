/*************************************************************************
	> File Name: common.c
	> Author: 
	> Mail: 
	> Created Time: Sat 08 Aug 2020 02:31:02 PM CST
 ************************************************************************/

#include"head.h"

char conf_value_ans[512] = {0};

int make_non_block(int fd) {
    int flag;
    if ((flag = fcntl(fd, F_GETFL)) < 0) {
        return -1;
    }
    // 不能单纯写 fcntl(fd, ..., O_NONBLOCK)，原来的属性丢了
    flag |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flag);
    return 0;
}

int make_block(int fd) {
    int flag;
    if ((flag = fcntl(fd, F_GETFL)) < 0) {
        return -1;
    }
    flag &= ~O_NONBLOCK;
    fcntl(fd, F_SETFL, flag);
    return 0;
}

char *get_conf(const char *conf, const char *key) {
    FILE *file = NULL;
    if (conf == NULL || key == NULL) {
        errno = EINVAL;
        return NULL;
    }

    if ((file = fopen(conf, "r")) == NULL) {
        perror("fopen()");
        exit(1);
    }

    memset(conf_value_ans, 0, sizeof(conf_value_ans));

    char tmp[512] = {0};

    while (fgets(tmp, sizeof(tmp), file) != NULL) {
        if (strstr(tmp, key) != NULL) {
            strncpy(conf_value_ans, tmp + strlen(key) + 1, strlen(tmp) - strlen(key) - 2);
            break;
        }
        memset(tmp, 0, sizeof(tmp));
    }
    fclose(file);
    return conf_value_ans;
}


int socket_create(int port) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }
    int val;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int)) < 0) {
        return -1;
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr("0.0.0.0");

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return -1;
    }

    if (listen(sockfd, 10) < 0) {
        return -1;
    }

    return sockfd;
}

int socket_connect(char *ip, int port) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return -1;
    }
    return sockfd;
}

int socket_create_udp(int port) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM | FNONBLOCK, 0)) < 0) {
        return -1;
    }
    int val;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int)) < 0) {
        return -1;
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr("0.0.0.0");

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return -1;
    }
    return sockfd;
}

int socket_udp() {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return -1;
    }
    return sockfd;
}
