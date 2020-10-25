/*************************************************************************
	> File Name: 4.udp_epoll.h
	> Author: 
	> Mail: 
	> Created Time: Wed 21 Oct 2020 07:59:10 PM CST
 ************************************************************************/

#ifndef _4UDP_EPOLL_H
#define _4UDP_EPOLL_H

void add_event_ptr(int epollfd, int fd, int events, struct User *user);
void del_event(int epollfd, int fd);
int udp_connect(struct sockaddr_in *client);
int udp_accept(int fd, struct User *user);
#endif
