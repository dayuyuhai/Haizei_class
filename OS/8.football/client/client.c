/*************************************************************************
	> File Name: temp.c
	> Author: wei 
	> Mail: 1931248856@qq.com 
	> Created Time: Fri Oct 23 19:58:59 2020
 ************************************************************************/

#include "../common/head.h"
#include "../common/client_recv.h"
#include "../common/game_ui.h"
#include "../common/send_chat.h"
#include "../common/send_ctl.h"
#include "../common/show_strength.h"
#include "../common/common.h"
#include "../common/server_re_draw.h"
#include "../common/show_data_stream.h"
#include "../common/ball_status.h"
#include "../common/udp_epoll.h"
int server_port = 0;
char server_ip[20] = {0};
int team = -1;
char *conf = "./football.conf";
int sockfd = -1;
struct Map court;
struct Bpoint ball;
struct FootBallMsg chat_msg;
struct FootBallMsg ctl_msg;
int show_name = 0;
char data_stream[20];
WINDOW *Football, *Message, *Help, *Score, *Write, *Football_t;
int message_num = 0;
struct BallStatus ball_status;
struct Score score;
struct User* rteam, *bteam;


void logout(int signum) {
	struct FootBallMsg msg;
	msg.type = FT_FIN;
	send(sockfd, (void *)&msg, sizeof(msg), 0);
    close(sockfd);
    DBG(RED"Bye!\n"NONE);
	endwin();
	exit(1);
}

int main(int argc, char **argv) {
    int opt;
    struct LogRequest request;
    struct LogResponse response;
    bzero(&request, sizeof(request));
    bzero(&response, sizeof(response));
    bzero(&chat_msg, sizeof(struct FootBallMsg));
    bzero(&ctl_msg, sizeof(struct FootBallMsg));
    chat_msg.type = FT_WALL;
    ctl_msg.type = FT_CTL;
    while ((opt = getopt(argc, argv, "h:p:t:m:n:")) != -1) {
        switch (opt) {
            case 'h' : strcpy(server_ip, optarg); break;
            case 'p' : server_port = atoi(optarg); break;
            case 'm' : strcpy(request.msg, optarg); break;
            case 't' : request.team = atoi(optarg);  break;
            case 'n' : strcpy(request.name, optarg); break;
            default:
            fprintf(stderr, "Usage : %s [-hptmn]!\n", argv[0]);
            exit(1);
        }
    }
    //请判断如果启动参数中没有这些配置，从配置文件中读取
    DBG(GREEN"Checking config file...\n");
    if (!request.name[0]) strcpy(request.name, get_conf_value(conf, "NAME"));
    if (request.team == -1) request.team = team = atoi(get_conf_value(conf, "TEAM"));
    if (!request.msg[0]) strcpy(request.msg, get_conf_value(conf, "LOGMSG"));
    if (!server_ip[0]) strcpy(server_ip, get_conf_value(conf, "SERVERIP"));
    if (!server_port)server_port = atoi(get_conf_value(conf, "SERVERPORT"));
    DBG(GREEN"Name=%s, team=%d, msg=%s, IP=%s, port=%d\n"NONE,request.name, request.team, request.msg ,server_ip, server_port);

    DBG(GREEN"server init...\n"NONE);
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);
    server.sin_addr.s_addr = inet_addr(server_ip);
    socklen_t len = sizeof(server);
    if ((sockfd = socket_udp()) < 0) {
        perror("socket_udp()");
        exit(1);
    }
    sendto(sockfd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&server, len);
    //  在这里，请使用select做定时，如果超过时间没有收到数据，判定为server不在线
    //  retval就是select的返回值
    fd_set set;
	FD_ZERO(&set);
	FD_SET(sockfd, &set);
	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;
    int retval = select(sockfd + 1, &set, NULL, NULL, &tv);
    if (retval == -1) {
        perror("select");
        exit(1);
    } else if (retval){
        int ret = recvfrom(sockfd, (void *)&response, sizeof(response), 0, (struct sockaddr *)&server, &len);
        if (ret != sizeof(response) || response.type) {
            printf("The Game Server refused your login.\n\tThis May be helpful:%s\n", response.msg);
            exit(1);
        }
    } else {
        printf("The Game Server is out of service!.\n");
        exit(1);
    }
    DBG(GREEN"SERVER : "NONE" %s\n", response.msg);
    connect(sockfd, (struct sockaddr *)&server, len);

#ifndef _D
   // initfootball();
#endif

    signal(SIGALRM, send_ctl);
    struct itimerval itimer;
    itimer.it_interval.tv_sec = 0;
    itimer.it_interval.tv_usec = 100000;
    itimer.it_value.tv_sec = 0;
    itimer.it_value.tv_usec = 100000;

    //内核维护一个时钟信号
    setitimer(ITIMER_REAL, &itimer, NULL);

    while (1) {
        DBG(GREEN"Please input\n"NONE);
        int c = getchar();
        printf(GREEN"input:%c\n"NONE, c);
        switch (c) {
            case 'a':
            ctl_msg.ctl.dirx -= 1;
            break;
            case 'd':
            ctl_msg.ctl.dirx += 1;
            break;
            case 'w':
            ctl_msg.ctl.diry -= 1;
            break;
            case 's':
            ctl_msg.ctl.diry += 1;
            break;
            case 13:
            send_chat();
            break;
            case ' ':
            show_strength();
            break;
            case 'k': {
                show_data_stream('k');
                struct FootBallMsg msg;
                bzero(&msg, sizeof(struct FootBallMsg));
                msg.type = FT_CTL;
                msg.ctl.action = ACTION_KICK;
                msg.ctl.strength = 3;
                send(sockfd, (void *)&msg, sizeof(msg), 0);
            }
            break;
            default:
            break;
        }
    }

    sleep(10);    return 0;
    }
