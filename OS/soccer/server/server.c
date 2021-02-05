/*************************************************************************
	> File Name: server.c
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年10月21日 星期三 19时14分44秒
 ************************************************************************/

#include "../common/head.h"
#include "../common/thread_pool.h"
#include "../common/common.h"
#include "../common/sub_reactor.h"
#include "../common/heart_beat.h"
#include "../common/game_ui.h"
#include "../common/server_exit.h"
#include "../common/server_re_draw.h"
#include "../common/show_data_stream.h"
#include "../common/ball_status.h"
#include "../common/udp_epoll.h"

char *conf = "./football.conf";
struct Map court;
struct Bpoint ball;
struct BallStatus ball_status;
struct Score score;
int repollfd, bepollfd;
struct User* rteam, *bteam;
int port = 0, message_num = 0; //服务端等待客户接入的端口，设置为全局
char data_stream[20] = {0};
pthread_mutex_t rmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t bmutex = PTHREAD_MUTEX_INITIALIZER;
WINDOW *Football, *Football_t, *Message, *Help, *Score, *Write;
#define MAX 50

void *drew(void *arg) {
        initfootball();
    while (1) {
        sleep(15);
    }
    return NULL;
}

//全局变量存储于数据区(全局区)，更好的实现是传参

int main(int argc, char **argv) {
    int opt, listener, epollfd;
    //listener:监听连接
    pthread_t ret_t, blue_t, heart_t;
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
            case 'p' :
                port = atoi(optarg);
                break;
            default : 
                fprintf(stderr, "Usage : %s -p port\n", argv[0]);
                exit(1);
        }
    }
    argc -= (optind - 1);
    argv += (optind - 1);

    if (argc > 1) {
        fprintf(stderr, "Usage: %s [-p port]\n", argv[0]);
        exit(1);
    }
    //使nurse库支持中文
    setlocale(LC_ALL, "");
    if (!port) port = atoi(get_conf_value(conf, "PORT"));
    court.width = atoi(get_conf_value(conf, "COLS"));
    court.height = atoi(get_conf_value(conf, "LINES"));
    printf("port = %d, width = %d, height = %d\n", port, court.width, court.height);
    DBG("port = %d, width = %d, height = %d\n", port, court.width, court.height);
    court.start.x = 3;
    court.start.y = 3;

    ball.x = court.width / 2;
    ball.y = court.height / 2;
    
    bzero(&ball_status, sizeof(ball_status));
    ball_status.by_team = -1;
    bzero(&score, sizeof(score));

    if ((listener = socket_create_udp(port)) < 0) {
        perror("socket_create_udp()");
        exit(1);
    }

    DBG(GREEN"INFO"NONE" : server start On port!\n");

#ifndef _D 
    pthread_t drew_t;
    pthread_create(&drew_t, NULL, drew, NULL);
#endif

    rteam = (struct User *)calloc(MAX, sizeof(struct User));
    bteam = (struct User *)calloc(MAX, sizeof(struct User));

    epollfd = epoll_create(MAX * 2);
    repollfd = epoll_create(MAX);
    bepollfd = epoll_create(MAX);

    if (epollfd < 0 || repollfd < 0 || bepollfd < 0) {
        perror("epoll_create()");
        exit(1);
    }
    
    struct task_queue redQueue;
    struct task_queue blueQueue;

    task_queue_init(&redQueue, MAX, repollfd);
    task_queue_init(&blueQueue, MAX, bepollfd);

    pthread_create(&ret_t, NULL, sub_reactor, (void *)&redQueue);
    pthread_create(&blue_t, NULL, sub_reactor, (void *)&blueQueue);
    pthread_create(&heart_t, NULL, heart_beat, NULL);

    signal(SIGINT, server_exit);

    struct epoll_event ev, events[MAX * 2];
    ev.events = EPOLLIN;
    ev.data.fd = listener;

    signal(SIGALRM, re_drew);

    struct itimerval itimer;
    itimer.it_interval.tv_sec = 0;
    itimer.it_interval.tv_usec = 100000;
    itimer.it_value.tv_sec = 5;
    itimer.it_value.tv_usec = 0;

    //内核维护一个时钟信号
    setitimer(ITIMER_REAL, &itimer, NULL);

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listener, &ev) < 0) {
        perror("epoll_ctl");
        exit(1);
    }

    struct sockaddr_in client;
    bzero(&client, sizeof(client));
    socklen_t len = sizeof(client);

   // Show_Message( , , "Waiting for Login." 1);
    
    //使下面的程序不受时钟信号的影响
    sigset_t origmask, sigmask;
    sigemptyset(&sigmask);
    sigaddset(&sigmask, SIGALRM);
    
    while (1) {
        DBG(YELLOW"Main Reactor" NONE " ; Waiting for client.\n");
        pthread_sigmask(SIG_SETMASK, &sigmask, &origmask);
        int nfds = epoll_wait(epollfd, events, MAX * 2, -1);
        pthread_sigmask(SIG_SETMASK, &origmask, NULL);
        if (nfds < 0) {
            perror("main : epoll_wait()");
            exit(1);
        }
        for (int i = 0; i < nfds; i++) {
            char buff[512] = {0};
            struct User user;
            bzero(&user, sizeof(user));
            DBG(YELLOW"EPOLL"NONE" :  Doing with %dth fd\n", i);
            if (events[i].data.fd == listener) {
                int new_fd = udp_accept(listener, &user);
                if (new_fd > 0) {
                    sprintf(buff, "%s login the Game.", user.name);
					DBG(YELLOW"Main thread"NONE" : Add %s to %s sub_reactor.\n", user.name, (user.team ? "BLUE": "RED"));
                    //Show_Message( , , buff, 1);
                    show_data_stream('l');
                    add_to_sub_reactor(&user);
                }
            } else {
                DBG(PINK"RECV"NONE" : %s\n", buff);
            }
        }
    } 

    return 0;
}
