/*************************************************************************
	> File Name: client_recv.c
	> Author: wei 
	> Mail: 1931248856@qq.com 
	> Created Time: Sat Nov  7 14:58:49 2020
 ************************************************************************/

#include "head.h"
#include "game_ui.h"
#include "server_re_draw.h"
#include "datatype.h"

extern int sockfd;

void *client_recv(void *arg) {
	while (1) {
		struct FootBallMsg msg;
		struct User user;
		bzero(&msg, sizeof(msg));
		recv(sockfd, (void *)&msg, sizeof(msg), 0);
		strcpy(user.name, msg.name);
		user.team = msg.team;
		if (msg.type & FT_HEART) {
			DBG(RED"HeartBeat from Server 心跳\n"NONE);
			msg.type = FT_ACK;
			send(sockfd, (void *)&msg, sizeof(msg), 0);
		} else if (msg.type & FT_MSG) {
			DBG(GREEN"%s : "NONE"%s\n", user.name, msg.msg);
		//	Show_Message( , &user, msg.msg, 0);
		} else if (msg.type & FT_WALL) {
			DBG(GREEN"Server Msg: "NONE"%s\n", msg.msg);
		//	Show_Message( , NULL, msg.msg, 1);
		} else if (msg.type & FT_FIN) {
			DBG(GREEN"Server is going to stop!\n"NONE);
            close(sockfd);
			endwin();	
			exit(0);
		} else if (msg.type & FT_MAP) {
			//cJSON *root = cJSON_Parse(msg.msg);
			//re_drew(root);
            DBG(GREEN"re_drew\n"NONE);
		} else if (msg.type & FT_SCORE) {
            DBG(GREEN"score\n"NONE);
		} else {
			DBG(GREEN"Server Msg :"NONE"Unsupport Message Type.\n");
		}
	}
}
