/*************************************************************************
	> File Name: common.c
	> Author: weier 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年08月08日 星期六 14时31分11秒
 ************************************************************************/

// static extern

#include "head.h"
char conf_ans[512];

int socket_udp() {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return -1;
    }
    make_non_block(sockfd);
    return sockfd;
}

int socket_create_udp(int port) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return -1;
    }

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    //server.sin_addr.s_addr = inet_addr("0.0.0.0");
    server.sin_addr.s_addr = INADDR_ANY;
    
    int val = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(int)) < 0) {
        return -1;
    }
    make_non_block(sockfd);

    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return -1;
    }
    return sockfd;
}

char *get_conf_value(const char *path, const char *key) {
    FILE *fp = NULL;
    char *line = NULL, *sub = NULL;
    ssize_t nread = 0, len = 0;
    if (path == NULL || key == NULL) {
        errno = EINVAL;
        return NULL;
    }
    if ((fp = fopen(path, "r")) == NULL) {
        errno = EINVAL;
        return NULL;
    }
    while ((nread = getline(&line, &len, fp)) != -1) {
        if ((sub = strstr(line, key)) == NULL) {
            continue;
        }
        if (line[strlen(key)] == '=') {
            strncpy(conf_ans, sub + strlen(key) + 1, nread - strlen(key) - 2);
            *(conf_ans + nread - strlen(key) - 2) = '\0';
            break;
        }
    } 
    free(line);
    fclose(fp);
    if (sub == NULL) return NULL;
    return conf_ans;
}

int make_non_block(int fd) {
    int flag; 
    if ((flag = fcntl(fd, F_GETFL)) < 0) {
        return -1;
    }
    //flag |= O_NONBLOCK;
    fcntl(fd, F_SETFL, flag|O_NONBLOCK);
    return 0;
}

int make_block(int fd) {
    int flag; 
    if ((flag = fcntl(fd, F_GETFL)) < 0) {
        return -1;
    }
    fcntl(fd, F_SETFL, flag&~O_NONBLOCK);
    return 0;
}

int socket_create(int port) {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }
    int val = 1;
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
    //if (setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &tv, optlen) < 0){
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    //server.sin_addr.s_addr = inet_addr("0.0.0.0");
    server.sin_addr.s_addr = inet_addr(ip);

    if ((connect(sockfd, (struct sockaddr *)&server, sizeof(server))) < 0) {
        return -1;
    }
    
    return sockfd;
}

