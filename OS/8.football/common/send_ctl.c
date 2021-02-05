/*************************************************************************
	> File Name: send_ctl.c
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年11月07日 星期六 11时31分05秒
 ************************************************************************/

#include "head.h"
#include "show_data_stream.h"
extern int sockfd;
extern struct FootBallMsg ctl_msg; //也是个全局变量
void send_ctl() {
    if (ctl_msg.ctl.dirx || ctl_msg.ctl.diry) {
        ctl_msg.ctl.action = ACTION_DFT;
        send(sockfd, (void *)&ctl_msg, sizeof(ctl_msg), 0);
        ctl_msg.ctl.dirx = ctl_msg.ctl.diry = 0;
        show_data_stream('n');
    }
}
