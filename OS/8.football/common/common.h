/*************************************************************************
	> File Name: common.h
	> Author: weier 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年08月08日 星期六 14时31分19秒
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H
int make_non_block(int fd);
int make_block(int fd);
int socket_create(int port);
int socket_connect(char *ip, int port);
char *get_conf_value(const char *path, const char *key);
int socket_create_udp(int port);
int socket_udp();
#endif

