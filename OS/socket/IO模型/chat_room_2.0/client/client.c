/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Wed 19 Aug 2020 03:19:42 PM CST
 ************************************************************************/

#include "head.h"
char *conf = "./chat.conf";
char name[20] = {0};
char server_ip[20] = {0};
int sockfd;

/*
WINDOW *msg_win, *sub_msg_win, *input_win, *sub_input_win, *help_win, *sub_help_win;
int msgnum;
*/

void logout(int signum) {
    struct ChatMsg msg;
    bzero(&msg, sizeof(msg));
    msg.type = CHAT_FIN;
    send(sockfd, (void *)&msg, sizeof(msg), 0);
    if (recv(sockfd, (void *)&msg, sizeof(msg), 0) <= 0) {
        /*
        sprintf(msg.msg, "Bye");
        print_message(sub_msg_win, &msg, 1);
        sleep(1);
        endwin();
        */
        exit(1);
    }
    /*
    if (msg.type & CHAT_FIN_1) {
        printf(GREEN"Bye\n"NONE);
        exit(0);
    }
    */
}

int main(int argc, char **argv) {
    int opt, server_port = 0;

    pthread_t recv_t;

    while ((opt = getopt(argc, argv, "h:p:n:"))  != -1) {
        switch (opt) {
            case 'h':
                strcpy(server_ip, optarg);
                break;
            case 'p':
                server_port = atoi(optarg);
                break;
            case 'n':
                strcpy(name, optarg);
                break;
            default:
                fprintf(stderr, "Usage : %s ip port name!\n", argv[0]);
                exit(1);
        }
    }
    if (!server_port) server_port = atoi(get_conf(conf, "SERVERPORT"));
    if (!strlen(server_ip)) strcpy(server_ip, get_conf(conf, "SERVERIP"));
    if (!strlen(name)) strcpy(name, get_conf(conf, "NAME"));

    setlocale(LC_ALL, ""); // 支持中文

    DBG(GREEN"INFO"NONE" : server_ip = %s, server_port = %d, name = %s\n",
       server_ip, server_port, name);

    if ((sockfd = socket_connect(server_ip, server_port)) < 0) {
        perror("socket_connect()");
        exit(1);
    }

    DBG(GREEN"INFO"NONE" : connected to server via TCP\n");;

    struct ChatMsg msg;
    bzero(&msg, sizeof(msg));
    strcpy(msg.name, name);
    msg.type = CHAT_SYN;
    send(sockfd, (void *)&msg, sizeof(msg), 0);

    bzero(&msg, sizeof(msg));

    recv(sockfd, (void *)&msg, sizeof(msg), 0);

    DBG(GREEN"INFO"NONE" : recved packet from server\n");

    if (msg.type & CHAT_NAK) {
        DBG(RED"server returned eooro"NONE" ; login failed :%s\n", msg.msg);
        exit(1);
    }

    DBG(RED"Login success"NONE" ; login success :%s\n", msg.msg);

    signal(SIGINT, logout);

    pthread_create(&recv_t, NULL, client_recv, NULL);

    // init_ui();

    strcpy(msg.name, name);
    // echo();
    // nocbreak();

    while (1) {
        msg.type = CHAT_PUB;
        bzero(msg.msg, sizeof(msg.msg));

        /*
        w_gotoxy_puts(sub_input_win, 1, 1, "Input :");
        mvwscanw(sub_input_win, 2, 2, "%[^\n]s", msg.msg);
        */

        scanf("%[^\n]s", msg.msg);
        getchar();
        // if (!strlen(msg.msg)) continue;
        if (msg.msg[0] == '@') msg.type = CHAT_PRI;
        if (msg.msg[0] == '#') {
            msg.type = CHAT_FUNC;
            // if (msg.msg[1] == '1') msg.opt = FUNC_CHECK_ONLINE;
            // if (msg.msg[1] == '2') msg.opt = FUNC_CHANGE_NAME;
        }
        send(sockfd, (void *)&msg, sizeof(msg), 0);
        /*
        wclear(input_win);
        box(input_win, 0, 0);
        wrefresh(input_win);
        */
    }

    
    return 0;
}
