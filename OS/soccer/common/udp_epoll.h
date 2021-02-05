/*************************************************************************
	> File Name: udp_epoll.h
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年10月21日 星期三 19时15分10秒
 ************************************************************************/

#ifndef _UDP_EPOLL_H
#define _UDP_EPOLL_H
void add_event_ptr(int epollfd, int fd, int events, struct User *user);
void del_event(int epollfd, int fd);
//int udp_connect(struct sockaddr_in *client);
int udp_accept(int fd, struct User *user);
void add_to_sub_reactor(struct User *user);
int check_online(struct LogRequest *request);

#endif
