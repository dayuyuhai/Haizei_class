/*************************************************************************
	> File Name: user.h
	> Author: 
	> Mail: 
	> Created Time: Sun 16 Aug 2020 09:54:10 AM CST
 ************************************************************************/

#ifndef _USER_H
#define _USER_H

#define MAXUSER 100

struct User {
    char name[20];
    char chat_name[20];
    char real_name[20];
    int flag;
    int fd;
    char ip[20];
    int online;

};


#define CHAT_SYN 0x01
#define CHAT_FIN 0x02
#define CHAT_ACK 0x04
#define CHAT_HEART 0x08
#define CHAT_PRI 0x10
#define CHAT_PUB 0x20
#define CHAT_FUNC 0x40
#define CHAT_SYS 0x80
#define CHAT_NAK 0x100
#define CHAT_FIN_1 0x200
#define FUNC_CHECK_ONLINE 0x01
#define FUNC_CHANGE_NAME 0x02


struct ChatMsg {
    int type;
    int opt;
    char name[20];
    char msg[1024];
};

struct FileMsg {
    char name[512];
    long size;
    char buff[4096];
};

void *thread_send(void *arg);
void *thread_recv(void *arg);
void deal_send_message(char *buff, struct ChatMsg *c_msg);
void deal_recv_message(struct ChatMsg *c_msg, int fd);

#endif
