/*************************************************************************
	> File Name: ball_status.c
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年11月01日 星期日 16时45分47秒
 ************************************************************************/

#include "head.h"
#include "game_ui.h"
#include <math.h>
extern WINDOW *Message;
extern struct Bpoint ball;
extern struct BallStatus ball_status;

#define PI 3.1415926

int can_kick(struct Point *loc, int strength){
    //palyer和ball坐标对齐
    //判断palyer和ball的坐标在上下左右2个单位距离内，则可踢球
    //根据player和ball的相对位置，计算球的运动方向，加速度方向，假设球只能在palyer和ball的延长线上运动
    //假设player踢球的接触时间为0.2秒，默认加速度为40，力度增加，加速度也增加
    //可踢返回1，否则返回0
    
    char tmp[512];
    sprintf(tmp, "loc->x = %d, (int)ball.x = %d, loc->y = %d, (int)ball.y = %d", loc->x - 2, (int)ball.x, loc->y, (int)ball.y);
    //Show_Message(Message, NULL, tmp, 1);
    if (abs(loc->x - 2 - (int)ball.x) <= 2 && abs(-loc->y + 1 + (int)ball.y) <= 2) {
        if (loc->x - 2 == (int)ball.x && loc->y - 1 == (int)ball.y) return 0;
        double v_tmp = (40.0 * strength) * 0.2;
        sprintf(tmp, "v_tmp = %lf", v_tmp);
        //Show_Message(Message, NULL, tmp, 1);
        double a;
        if (loc->x - 2 == (int)ball.x) {
            a = PI / 2;
        } else {
            a = atan(fabs(-loc->y + 1 + ball.y) / abs(loc->x - 2 - ball.x));
        }
        if (loc->x - 2 > ball.x) {
            ball_status.v.x =  -cos(a) * v_tmp;
            ball_status.a.x = cos(a) * 3;
        } else {
            ball_status.v.x =  cos(a) * v_tmp;
            ball_status.a.x = -cos(a) * 3;
        }
        if (-loc->y + 1 > -ball.y) {
            ball_status.v.y = +sin(a) * v_tmp;
            ball_status.a.y = -sin(a) * 3;
        } else {
            ball_status.v.y = -sin(a) * v_tmp;
            ball_status.a.y = +sin(a) * 3;
        }
        return 1;
    } else 
        return 0;
}

int can_access(struct Point *loc) {
	int px = loc->x;
	int py = loc->y;
	if (abs(px - (int)ball.x) <= 2 && abs(py - (int)ball.y) <= 2) {
		return 1;
	}
	return 0;
}

