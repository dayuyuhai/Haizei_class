/*************************************************************************
	> File Name: show_strength.c
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年11月01日 星期日 16时47分57秒
 ************************************************************************/

#include "head.h"
//客户端中，按下空格键，调用此函数
extern WINDOW *Write;
extern int sockfd;
void show_strength() {
    //在Write窗口中，显示踢球力度条，光标在进度条上快速移动
    //设置0文件为非阻塞IO
    //while 等待空格或者'k'键的按下，如果按下退出，取得当前的strength
    //通过sockfd向服务端发送控制信息，踢球
    int maxx, maxy, strength;
	getmaxyx(Write, maxy, maxx);
	struct FootBallMsg msg;
    bzero(&msg, sizeof(msg));
	for (int i = 2; i < maxx - 2; i++) {
		if (i < maxx / 5 || i > (maxx - maxx / 5)) {
			wattron(Write, COLOR_PAIR(8));
		} else if (i < 2 * (maxx / 5) || i > 3 * (maxx / 5)) {
			wattron(Write, COLOR_PAIR(9));
		} else {
			wattron(Write, COLOR_PAIR(10));
		}
		mvwaddch(Write, 2, i, " ");
		//mvwaddch(Write, 2, i, " ");
	}
	wattron(Write, COLOR_PAIR(3));
    int tmp[5] = {1, 2, 3, 2, 1};
    int offset =  1;
    int loc = 2;
	make_non_block(0);
	while (1) {
		char c = getchar();
		if ( c != -1) {
			if (c == ' ' || c == 'k') {
			    mvwaddch(Write, 1, loc, " ");
			    mvwaddch(Write, 3, loc, " ");
				make_block(0);
				break;
			}
		}
		usleep(5000);
		wattron(Write, COLOR_PAIR(3));
		mvwprintw(Write, 1, loc, " ");
		mvwprintw(Write, 3, loc, " ");
		loc += offset;
		mvwprintw(Write, 1, loc, "|");
		mvwprintw(Write, 3, loc, "|");
		mvwprintw(Write, 4, maxx, " ");
		if (loc >= maxx - 2) offset = -1;
		if (loc <= 2) offset = 1;
		wrefresh(Write);
	}
    char info[512] = {0};
    sprintf(info, "strength = %d", tmp[loc / (maxx / 5)]);
    //show_Message(, NULL, info, 1);
    msg.type = FT_CTL;
    msg.ctl.action = ACTION_KICK;
    strength = msg.ctl.strength = tmp[loc / (maxx / 5)];
    send(sockfd, (void *)&msg, sizeof(msg), 0);
}
