/*************************************************************************
	> File Name: server_send_all.h
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年10月30日 星期五 17时55分57秒
 ************************************************************************/

#ifndef _SERVER_SEND_ALL_H
#define _SERVER_SEND_ALL_H
void send_team(struct User *team, struct FootBallMsg *msg);
void send_all(struct FootBallMsg *msg);
#endif
