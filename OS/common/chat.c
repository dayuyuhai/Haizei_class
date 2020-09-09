/*************************mZ***********************************************
	> File Name: chat.c
	> Author: 
	> Mail: 
	> Created Time: Wed 19 Aug 2020 02:47:19 PM CST
 ************************************************************************/

#include "head.h"

extern struct User *users;
extern int epollfd;
extern int maxfd;
extern int cnt_online;

void *heart_beat(void *arg) {
    struct ChatMsg msg;
    msg.type = CHAT_HEART;
    while (1) {
        sleep(5);
        for (int i = 1; i <= maxfd; i++) {
            if (users[i].online == 1) {
                send(users[i].fd, (void *)&msg, sizeof(msg), 0);
                if (--users[i].flag <= 0) {
                    DBG(PURPLE"Heart Beat"NONE" ; %s is offline by heart_beat\n", users[i].name);
                    del_event(epollfd, &users[i]);
                    close(users[i].fd);
                    users[i].online = 0;
                    cnt_online--;
                }
            }
        }
    }
}

int find_sub(struct User *users, int max) {
    for (int i = 1; i < max; i++) {
        if (!users[i].online) {
            return i;
        }
    }
    return -1;
}

int judge_online(struct User *users, char *name, int max) {
    for (int i = 1; i < max; i++) {
        // if (users[i].online && !strcmp(name, users[i].chat_name)) {
        if (users[i].online && !strcmp(name, users[i].name)) {
            return users[i].fd;
        }
    }
    return 0;
}

void add_event(int epollfd, int fd, int events, struct User *user) {
    struct epoll_event ev;
    ev.events = events;
    ev.data.ptr = (void *)user;

    DBG(PURPLE"Main Reactor"NONE" : adding %s to main reactor\n", user->name);

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, fd, &ev) < 0) {
        perror("epoll_ctl()");
        exit(1);
    }


}


void del_event(int epollfd, struct User *user) {
    epoll_ctl(epollfd, EPOLL_CTL_DEL, user->fd, NULL);
    DBG(PURPLE"Main Reactor"NONE" : deleted %s from main reactor\n", user->name);
}


int do_login(struct User *user, struct ChatMsg *msg) {
    int online = 0;
    for (int i = 1; i <= maxfd; i++) {
        if (users[i].online && !strcmp(msg->name, users[i].name)) {
            online = 1;
        }
    }
    if (online) {
        DBG(YELLOW"Login error"NONE" : %s is already online\n", msg->name);
        sprintf(msg->msg, "%s is already online!", msg->name);
        msg->type = CHAT_NAK;
        user->online = 0;
        send(user->fd, msg, sizeof(struct ChatMsg), 0);
        close(user->fd);
        del_event(epollfd, user);
        return 1;
    }

    cnt_online++;
    DBG(L_GREEN"Login Success"NONE" : %s login success\n", msg->name);
    msg->type = CHAT_ACK;
    sprintf(msg->msg, "%s , you login success\n", msg->name);
    send(user->fd, msg, sizeof(struct ChatMsg), 0);
    user->online = 1;
    user->flag = 10;
    strcpy(user->name, msg->name);
    strcpy(user->chat_name, user->name);

    return 0;
}

