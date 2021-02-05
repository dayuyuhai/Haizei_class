/*************************************************************************
	> File Name: server_send_all.c
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年10月30日 星期五 17时54分01秒
 ************************************************************************/

#include "head.h" 
#define MAX 50
extern struct User *rteam, *bteam;
void send_team(struct User *team, struct FootBallMsg *msg){
    for (int i = 0; i < MAX; i++) {
        if (team[i].online) send(team[i].fd, (void *)msg, sizeof(struct FootBallMsg), 0);
    }
}
void send_all(struct FootBallMsg *msg) {
    send_team(rteam, msg);
    send_team(bteam, msg);
}
