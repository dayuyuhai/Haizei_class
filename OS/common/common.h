/*********mZ***************************************************************
	> File Name: common.h
	> Author: 
	> Mail: 
	> Created Time: Sat 08 Aug 2020 02:31:09 PM CST
 ************************************************************************/

#ifndef _COMMON_H
#define _COMMON_H

extern char conf_value_ans[512];

char *get_conf(const char *conf, const char *key);
int make_non_block(int fd);
int make_block(int fd);
int socket_create(int port);
int socket_connect(char *ip, int port);
#endif
