/*************************************************************************
	> File Name: server_re_draw.c
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年11月01日 星期日 17时18分51秒
 ************************************************************************/
#include "head.h"
#include "game_ui.h"
#include "server_exit.h"
#include "thread_pool.h"
#include "server_send_all.h"
#define MAX 50
extern struct User *rteam, *bteam;
extern WINDOW *Football, *Football_t;
extern struct BallStatus ball_status;
extern struct Map court;
extern struct Bpoint ball;
extern struct Score score;

void re_drew_ball() {
    //根据ball_status里记录的加速度，和上次re_drew时的速度，算出本次球应该移动的时间
    //加速度保持不变，速度更新
    //需要注意的是，当判断到速度减为，ball_status里的速度和加速度都清空
    //同样需要注意的时，球如果超过球场边界，则判定为出界，球停止到边界即可
    if (ball_status.v.x || ball_status.v.y) {
        char tmp[512] = {0};
        sprintf(tmp, "time out = %lf, ax = %lf, ay = %lf", sqrt(pow(ball_status.v.x, 2) + pow(ball_status.v.y, 2)) / sqrt(pow(ball_status.a.x, 2) + pow(ball_status.a.y, 2)), ball_status.a.x, ball_status.a.y );
        double t = 100000.0 / 1000000.0;
        //Show_Message(, NULL, tmp, 1);
        if (t >= sqrt(pow(ball_status.v.x, 2) + pow(ball_status.v.y, 2)) / sqrt(pow(ball_status.a.y, 2) + pow(ball_status.a.y, 2))) {
            //Show_Message(, NULL, tmp, 1);
            //Show_Message(, NULL, "time out", 1);
            bzero(&ball_status.v, sizeof(ball_status.v));
            bzero(&ball_status.a, sizeof(ball_status.a));
        } else {
            ball.x += (ball_status.v.x * t + ball_status.a.x * pow(t, 2) / 2);
            ball_status.v.x += ball_status.a.x * t;
            ball.y += (ball_status.v.y * t / 2 + ball_status.a.y * pow(t, 2) / 4);
            ball_status.v.y += ball_status.a.y * t;
            if (ball.x >= court.width || ball.x <= 0 || ball.y >= court.height || ball.y <= 0) {
                if (ball.x >= court.width - 1) {
                    if (ball.y >= court.height / 2 - 3 && ball.y <= court.height / 2 + 3) {
                        score.red++;
                        ball.x = court.width - 3;
                        ball.y = court.height / 2;
                        struct FootBallMsg msg;
                        msg.type = FT_WALL;
                        sprintf(msg.msg, "%s of %s team, get 1 score", ball_status.name, ball_status.by_team ? "blue" : "red");
                        send_all(&msg);
                    }
                    ball.x = court.width - 1;
                }
                if (ball.x <= 0) {
                    if (ball.y >= court.height / 2 - 3 && ball.y <= court.height / 2 + 3) {
                        score.blue++;
                        ball.x = 2;
                        ball.y = court.height / 2;
                        struct FootBallMsg msg;
                        msg.type = FT_WALL;
                        sprintf(msg.msg, "%s of %s team, get 1 score", ball_status.name, ball_status.by_team ? "blue" : "red");
                        send_all(&msg);
                    }
                    ball.x = 0;
                }
                if (ball.y >= court.height) ball.y = court.height - 1;
                if (ball.y <= 0) ball.y = 0;
                bzero(&ball_status.v, sizeof(ball_status.v));
                bzero(&ball_status.a, sizeof(ball_status.a));
                
            }
        }
    }
    w_gotoxy_putc(Football, (int)ball.x, (int)ball.y, 'o');
    if (ball_status.by_team) {
        wattron(Football, COLOR_PAIR(6));
    } else {
        wattron(Football, COLOR_PAIR(2));
    }
    w_gotoxy_putc(Football, (int)ball.x + 1, (int)ball.y, ACS_DEGREE);
    wattron(Football, COLOR_PAIR(3));

}
void  re_drew_player(int team, char *name, struct Point *loc) {
    //根据team，切换颜色
  //在loc位置打印player，并显示姓名
    char p = 'K';
    char blank[20] = {0};
    wattron(Football, COLOR_PAIR(team ? 6 : 2));
    w_gotoxy_putc(Football, loc->x, loc->y, p);
    w_gotoxy_puts(Football, loc->x + 1, loc->y - 1, name);
    wattroff(Football, COLOR_PAIR(team ? 6 : 2));
}
void re_drew_team(struct User *team) {
    //在team数组中，循环遍历用户，调用re_drew_palyer
    for (int i = 0; i < MAX; ++i) {
        if (!team[i].online) continue;
        re_drew_player(team[i].team, team[i].name, &team[i].loc);
    }
}

void re_drew_gate() {
    for (int i = (2 * court.height / 5); i <= (3 * court.height / 5); i++) {
		w_gotoxy_puts(Football_t, 1, i + 1, "x");
		w_gotoxy_puts(Football_t, court.width + 2, i + 1, "x");
	}
}

void re_drew(){
    //分别调用re_drew_team、re_drew_ball
    char tmp[512] = {0};
    werase(Football_t);
    box(Football, 0, 0);
    box(Football_t, 0, 0);
    re_drew_team(rteam);
    re_drew_team(bteam);
    re_drew_ball();
    wrefresh(Football_t);
}
