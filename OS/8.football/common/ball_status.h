/*************************************************************************
	> File Name: ball_status.h
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年11月01日 星期日 16时45分36秒
 ************************************************************************/

#ifndef _BALL_STATUS_H
#define _BALL_STATUS_H
int can_kick(struct Point *loc, int strength);
int can_access(struct Point *loc);
#endif
