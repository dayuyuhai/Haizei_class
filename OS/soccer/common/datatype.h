/*************************************************************************
	> File Name: datatype.h
	> Author: wei 
	> Mail: 1931248856@qq.com
	> Created Time: 2020年10月21日 星期三 19时09分58秒
 ************************************************************************/

#ifndef _DATATYPE_H
#define _DATATYPE_H
struct Point {
    int x;
    int y;
};
struct Bpoint {
    double x;
    double y;
};
struct User {
    int team; // 0 RED  1 BLUE
    int fd; //该玩家对应的连接
    char name[20];
    int online;// 1 在线 0 不在线
    int flag; //未响应次数
    struct Point loc;
};

//登录相关的
struct  LogRequest {
    char name[20];
    int team;
    char msg[512];
};
struct LogResponse{
    int type; // 0 OK 1 NO
    char msg[512];
};
struct Map {
    int width;
    int height;
    struct Point start;
    int gate_width;
    int gate_height;
};
//球加速度
struct Aspeed{
    double x;
    double y;
};
//球的速度
struct Speed{
    double x;
    double y;
};
//球的状态
struct BallStatus {
    struct Speed v;
    struct Aspeed a;
    int by_team;
    char name[20];
    //pthread_mutex_t mutex;
};
struct Score{
    int red;
    int blue;
};
//action value
#define ACTION_KICK 0x01
#define ACTION_CARRY 0x02
#define ACTION_STOP 0x04
#define ACTION_DFT 0x08
struct Ctl{
    int action;
    int dirx;
    int diry;
    int strength;
};
//type的值
#define FT_HEART 0x01 //心跳
#define FT_ACK 0x02   //ack
#define FT_MSG 0x04  //私聊，队友之间
#define FT_WALL 0x08 //公告
#define FT_CTL 0x10  //控制信息
#define FT_MAP 0x20 //场地数据
#define FT_FIN 0x40 //离场
#define FT_SCORE 0x80 //比分变化
#define FT_GAMEOVER 0x100 //gameover
#define MAX_MSG 1024
struct FootBallMsg {
    int type;
    int size;
    int team;
    char name[20];
    char msg[MAX_MSG];
    struct Ctl ctl;
};
#endif
