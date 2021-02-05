/*************************************************************************
	> File Name: server_exit.c
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年10月30日 星期五 17时51分03秒
 ************************************************************************/

#include "head.h"
#define MAX 50
extern struct User *rteam, *bteam;
void server_exit(int signum) {
    struct FootBallMsg msg;
    msg.type = FT_FIN;
    for (int i = 0; i < MAX; i++ ) {
        if (rteam[i].online) send(rteam[i].fd, (void *)&msg, sizeof(msg), 0);
        if (bteam[i].online) send(bteam[i].fd, (void *)&msg, sizeof(msg), 0);
    }
    endwin();
    exit(0);
}
