/*************************************************************************
	> File Name: client_func.c
	> Author: 
	> Mail: 
	> Created Time: Wed 19 Aug 2020 04:39:09 PM CST
 ************************************************************************/

#include "head.h"

/*
extern WINDOW *msg_win, *sub_msg_win, *input_win, *sub_input_win, *help_win, *sub_help_win;
extern int msgnum;
*/

extern int sockfd;

void *client_recv(void *arg) {
    struct ChatMsg msg;
    while (1) {
        memset(&msg, 0, sizeof(msg));
        if (recv(sockfd, (void *)&msg, sizeof(msg), 0) <= 0) {
            perror("client_recv()");
            exit(1);
        }
        if (msg.type & CHAT_PUB) {
            printf(BLUE"%s"NONE" : %s\n", msg.name, msg.msg);
            // print_message(sub_msg_win, &msg, 0);
        } else if (msg.type & CHAT_HEART) {
            DBG(RED"❤"NONE" : heart beat from server!\n");
            msg.type = CHAT_ACK;
            send(sockfd, (void *)&msg, sizeof(msg), 0);
        } else if (msg.type & CHAT_PRI) {
            printf(GRAY"%s"NONE" : %s\n", msg.name, msg.msg);
            // print_message(sub_msg_win, &msg, 0);
        } else if (msg.type & CHAT_SYS) {
            printf(GRAY"target user is not online\n"NONE);
            // print_message(sub_msg_win, &msg, 1);
        } else if (msg.opt & FUNC_CHECK_ONLINE) {
            printf("%s\n", msg.msg);
            // print_message(sub_msg_win, &msg, 1);
        } else if (msg.type & (CHAT_FIN_1 | CHAT_FIN)) {
            printf(GREEN"Bye (server)\n"NONE);
            // sprintf(msg.msg, "Bye!");
            // print_message(sub_msg_win, &msg, 1);
            exit(1);
        }
    }
}



