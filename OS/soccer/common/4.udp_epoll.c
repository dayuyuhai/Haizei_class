/*************************************************************************
mZ	> Created Time: Wed 21 Oct 2020 08:00:54 PM CST
 ************************************************************************/

#include "head.h"

extern int port;

void add_event_ptr(int epollfd, int fd, int events, struct User *user){
    struct epoll_event ev;

    ev.data.fd = fd;
    ev.events = events;
    ev.data.ptr = (void *)user;

    DBG(PURPLE"Main Reactor"NONE" : adding %s to main reactor\n", user->name);

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) < 0) {
        perror("epoll_ctl()");
        exit(1);
    }

    
}

void del_event(int epollfd, int fd) {
    epoll_ctl(epollfd, EPOLL_CTL_DEL, user->fd, NULL);
    DBG(PURPLE"Main Reactor"NONE" : deleted %s from main reactor\n", user->name);

}

int udp_connect(struct sockaddr_in *client) {
    int sockfd;
    if ((sockfd = socket_create_udp(client->sin_port)) == -1) {
         //fprintf(stderr, "socket_create_udp");
        return -1;
    }
    if (connect(sockfd, (struct sockaddr *)client, sizeof(struct sockaddr_in)) < 0) {
         //fprintf(stderr, "socket_udp_connect");
        return -1;
    }

    return sockfd;
}


int udp_accept(int fd, struct User *user) {
    int new_fd, ret;
    struct sockaddr_in client;
    struct LogRequest request;
    struct LogResponse response;

    memset(&request, 0, sizeof(request));
    memset(&response, 0, sizeof(response));


    socklen_t len = sizeof(client);
    
    ret = recvfrom(fd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&client, &len);
    if (ret != sizeof(struct LogRequest)) {
        response->type = 1;
        strcpy(response->msg, "Login failed with Data errors!");
        send(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, &len);
        return -1;
    }
    new_fd = udp_connect(&client);
    if (new_fd == -1) return -1;
    strcpy(user->name, request->name);
    user->team = request->team;
    user->fd = fd;

    response->type = 1;
    strcpy(response->msg, " Login Success, Enjoy Yourself");
    send(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, &len);
    return new_fd;
}
