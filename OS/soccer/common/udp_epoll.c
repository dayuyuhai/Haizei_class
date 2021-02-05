/*************************************************************************
	> File Name: udp_epoll.c
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年10月21日 星期三 19时15分00秒
 ************************************************************************/

#include "head.h"
#include "server_send_all.h"
#include "udp_epoll.h"
extern struct User *bteam, *rteam;
extern int repollfd, bepollfd;
extern pthread_mutex_t rmutex, bmutex;
extern struct Map court;
extern int port;
#define MAX 50 

void add_event_ptr(int epollfd, int fd, int events, struct User *user) {
    struct epoll_event ev;
    ev.events = events;
    ev.data.ptr = (void *)user;
    DBG(PINK"Main Reactor"NONE " : adding %s to main reacator\n", user->name);
    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) < 0) {
        perror("epoll_ctl()");
        exit(1);
    }
}

void del_event(int epollfd, int fd) {
    epoll_ctl(epollfd, EPOLL_CTL_DEL, fd, NULL);
}

int find_sub(struct User *team) {
    for (int i = 0; i < MAX; ++i) {
        if (!team[i].online) return i;
    }
    return -1;
}

int udp_connect(struct sockaddr_in *client){
    int sockfd;
    //connect到client
    if ((sockfd = socket_create_udp(port)) < 0) {
        perror("socket_create_udp");
        return -1;
    }
    //connect建立4元组过程, 可以send，recv, 连接
    if (connect(sockfd, (struct sockaddr *)client, sizeof(struct sockaddr)) < 0) {
        return -1;   
    }
    return sockfd;
}

//user指针需要在调用之前创建一个User结构体，然后将其地址传入，这是一个输出参数
int udp_accept(int fd, struct User *user) {
    int new_fd, ret;
    struct sockaddr_in client;
    struct LogRequest request;
    struct LogResponse response;
    bzero(&request, sizeof(request));
    bzero(response, szieof(response));
    socklen_t len = sizeof(client);
    //初始化必要的结构体
    ret = recvfrom(fd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&client, &len);
    //判断ret，也就是收到的字节数如果不等于LogRequest报文的大小
        //设置response报文，并告知对方此msg："Login failed with Data errors!
        //注意，你应该直接发送response报文
        //return -1

    if (ret != sizeof(request)) {
        response.type = 1;
        strcpy(response.msg, "Login failed with Data errors!");
        sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);
        return -1;
    }

    if (check_online(&request)) {
        response.type = 1;
        strcpy(response.msg, "You are Already Login!");
        sendto(fd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&client, len);
        return -1;

    }

    if (request.team) {
        DBG(GREEN"Info"NONE" : "BLUE"%s login on %s : %d <%s>\n", request.name, inet_ntoa(client.sin_addr), ntohs(client.sin_port), request.msg);
    } else {
        DBG(GREEN"Info"NONE" : "RED"%s login on %s : %d <%s>\n", request.name, inet_ntoa(client.sin_addr), ntohs(client.sin_port), request.msg);
    }

    //strcpy(user->ip, inet_ntoa(client.sin_addr));
    strcpy(user->name, request.name);
    user->team = request.team;

    //udp二元组, tcp四元组, 
    new_fd = udp_connect(&client);
    //判断如果new_fd为-1，应该return -1
    //拷贝request中的name到user指向的结构体中，当然还有team，fd等
    //send告知客户端：" Login Success, Enjoy Yourself"
    user->fd = new_fd;

    response.type = 0;
    char buff[512];
    sprintf(buff, "%s> Login Success, Enjoy Yourself, You have get for FootBall Project!\n", user->name);
    strcpy(response.msg, buff);
    send(new_fd, (void *)&response, sizeof(response), 0);
    return new_fd;
}

void add_to_sub_reactor(struct User *user) {
    struct User *team = (user->team ? bteam : rteam);
    DBG(YELLOW"Main Thread : "NONE"Add to sub_reactor\n");
    if (user->team) {
        pthread_mutex_lock(&bmutex);
    } else {
        pthread_mutex_lock(&rmutex);
    }

    int sub = find_sub(team);
    team[sub] = *user;
    team[sub].online = 1;
    team[sub].flag = 10;
    team[sub].loc.y = court.height + 1;
    if (user->team) {
        team[sub].loc.x = (court.width + 4) / 2 + 2 + 10 + sub;
    } else {
        team[sub].loc.x = (court.width + 4) / 2 + 2 - 10 + sub;
    }
    struct FootBallMsg r_msg;
    sprintf(r_msg.msg, "你的好友 %s 上线了，快打个招呼吧！", user->name);
    r_msg.type = FT_WALL;
    send_all(&r_msg);
    if (user->team) {
        pthread_mutex_unlock(&bmutex);
    } else {
        pthread_mutex_unlock(&rmutex);
    }
    DBG(L_RED"sub = %d, name = %s\n"NONE, sub, team[sub].name);
    if (user->team) {
        add_event_ptr(bepollfd, team[sub].fd, EPOLLIN || EPOLLET, &team[sub]);
    } else {
        add_event_ptr(repollfd, team[sub].fd, EPOLLIN || EPOLLET, &team[sub]);
    }
}

int check_online(struct LogRequest *request){
    for (int i = 0; i < MAX; i++) {
    //判断两个队伍中是否有同名用户，有的话返回1
        if (rteam[i].online && !strcmp(rteam[i].name, request->name)) return 1; 
        if (bteam[i].online && !strcmp(bteam[i].name, request->name)) return 1; 
    }
    return 0;
}
