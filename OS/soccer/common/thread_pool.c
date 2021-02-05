/*************************************************************************
	> File Name: thread_pool.c
	> Author: suyelu 
	> Mail: suyelu@126.com
	> Created Time: Tue 04 Aug 2020 04:22:05 PM CST
 ************************************************************************/

#include "head.h"
#include "thread_pool.h"
#include "udp_epoll.h"
#include "game_ui.h"
#include "show_data_stream.h"
#include "ball_status.h"
#include "./server_send_all.h"
extern int epollfd;
extern int repollfd, bepollfd;
extern struct User *bteam, *rteam;
extern struct BallStatus ball_status;
extern struct Bpoint ball;
extern struct Map court;
#define MAX 50

void do_work(struct User *user) {
    struct FootBallMsg msg;
    bzero(&msg, sizeof(msg));
    char buff[512] = {0};
    DBG(BLUE"wait do_work\n"NONE);
    int size = recv(user->fd, (void *)&msg, sizeof(msg), 0);
    DBG(BLUE"recv success ! do_work\n"NONE);
    user->flag = 10;
    if (msg.type & FT_ACK) {
        if (user->team) {
            DBG(L_BLUE"%s"NONE " heart \n", user->name);        
        } else {
            DBG(L_RED"%s"NONE " heart \n", user->name);        
        }
    } else if (msg.type & (FT_WALL | FT_MSG)) {
        if (user->team) {
            DBG(L_BLUE"%s"NONE " %s\n", user->name, msg.msg);        
        } else {
            DBG(L_RED"%s"NONE " %s\n", user->name, msg.msg);        
        }
        strcpy(msg.name, user->name);
        msg.team = user->team;
        send_all(&msg);
    } else if (msg.type & FT_FIN) {
        DBG(RED"%s logout. \n", user->name);
        sprintf(buff, "%s Logout.", user->name);
        //加锁, 有线程并发问题，online为0，仍发消息
        user->online = 0;
        int epollfd_tmp = (user->team ? bepollfd : repollfd);
        del_event(epollfd_tmp, user->fd);

    } else if (msg.type & FT_CTL) {
        sprintf(buff, "Ctrl Message kick = %d", msg.ctl.strength);
        if (msg.ctl.action & ACTION_DFT) {
            user->loc.x += msg.ctl.dirx;
            user->loc.y += msg.ctl.diry;
            if (user->loc.x <= 1) user->loc.x = 1;
            if (user->loc.x >= court.width + 2) user->loc.x = court.width + 2;
            if (user->loc.y <= 0) user->loc.x = 0;
            if (user->loc.y >= court.height + 2) user->loc.y = court.height + 2;
        }
        else if (msg.ctl.action & ACTION_KICK) {
            show_data_stream('k');
            user->loc.x = ball.x, user->loc.y = ball.y;
            sprintf(buff, "bx = %lf, by = %lf, px = %d, py = %d", ball.x, ball.y, user->loc.x, user->loc.y);
            //Show_Message(, user, buff, 0);
                DBG(BLUE"%s\n"NONE, buff);
            if (can_kick(&user->loc, msg.ctl.strength)) {
                DBG(BLUE"You can kick!\n"NONE); 
                ball_status.by_team = user->team;
                strcpy(ball_status.name, user->name);
                sprintf(buff, "vx = %f, vy = %f, ax = %f, ay = %f", ball_status.v.x, ball_status.v.y, ball_status.a.x, ball_status.a.y);
                DBG(BLUE"%s\n"NONE, buff);
                // Show_Message(, user, buff, 0);
            } else  {
                DBG(BLUE"You can not kick!\n"NONE); 
            }
        } else if (msg.ctl.action & ACTION_STOP) {
            show_data_stream('s');
            if (can_access(&user->loc)) {
                bzero(&ball_status.v, sizeof(ball_status.v));
                bzero(&ball_status.a, sizeof(ball_status.a));
                sprintf(buff, "Stop the Ball");
                // Show_Message(, user, buff, 0);
            }
        } else if (msg.ctl.action & ACTION_CARRY) {
            show_data_stream('c');
            sprintf(buff, "Try Carry the BAll");
            //Show_Message(, user, buff, 0);
        }
}
}

void task_queue_init(struct task_queue *taskQueue, int sum, int epollfd) {
	taskQueue->sum = sum;
	taskQueue->epollfd = epollfd;
	taskQueue->team = calloc(sum, sizeof(void *));
	taskQueue->head = taskQueue->tail = 0;
	pthread_mutex_init(&taskQueue->mutex, NULL);
	pthread_cond_init(&taskQueue->cond, NULL);
}

void task_queue_push(struct task_queue *taskQueue, struct User *user) {
	pthread_mutex_lock(&taskQueue->mutex);
	taskQueue->team[taskQueue->tail] = user;
	DBG(L_GREEN"Thread Pool : "NONE" Task Push %s \n", user->name);
	if (++taskQueue->tail == taskQueue->sum) {
		DBG(L_GREEN"Thread Pool : "NONE" Task Queue End.\n");
		taskQueue->tail = 0;
	}
	pthread_cond_signal(&taskQueue->cond);
	pthread_mutex_unlock(&taskQueue->mutex);
}

struct User *task_queue_pop(struct task_queue *taskQueue) {
	pthread_mutex_lock(&taskQueue->mutex);
	while (taskQueue->tail == taskQueue->head) {
		DBG(L_GREEN"Thread Pool : "NONE" Task Queue Empty, Waiting for Task.\n");
		pthread_cond_wait(&taskQueue->cond, &taskQueue->mutex);
	}
	struct User *user = taskQueue->team[taskQueue->head];
	DBG(L_GREEN"Thread Pool : "NONE" Task Pop %s.\n", user->name);
	if (++taskQueue->head == taskQueue->sum) {
		DBG(L_GREEN"Thread Pool : "NONE" Task Queue End.\n");
		taskQueue->head = 0;

	}
	pthread_mutex_unlock(&taskQueue->mutex);
	return user;
}

void *thread_run(void *arg) {
	pthread_t tid = pthread_self();
	pthread_detach(tid);
	struct task_queue *taskQueue = (struct task_queue *)arg;
	while (1) {
		struct User *user = task_queue_pop(taskQueue);
        do_work(user);
	}
}
