/*************************************************************************
	> File Name: heart_beat.c
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年10月30日 星期五 17时48分35秒
 ************************************************************************/

#include "head.h"
#include "datatype.h"
#include "udp_epoll.h"
#include "game_ui.h"
#include "show_data_stream.h"
#define MAX 50
extern struct User *rteam, *bteam;
extern int repollfd, bepollfd;

void heart_beat_team(struct User *team) {
    struct FootBallMsg msg;
    msg.type = FT_HEART;
    for (int i = 0; i < MAX; ++i) {
        if (!team[i].online) continue;
        if (!team[i].flag) {
            team[i].online = 0;
            continue;
        }
        send(team[i].fd, (void *)&msg, sizeof(msg), 0);
        team[i].flag--;
        if (team[i].flag <= 0) {
            show_data_stream('e');
            char tmp[512] = {0};
            team[i].online = 0;
            int tmpFd = (team[i].team ? bepollfd : repollfd);
            del_event(tmpFd, team[i].fd);
        }
    }
}
void *heart_beat(void *arg) {
    //死循环，固定时间调用heart_beat_team
    while (1) {
        sleep(10);
        heart_beat_team(bteam);
        heart_beat_team(rteam);
    }
}
