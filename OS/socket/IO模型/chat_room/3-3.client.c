/*************************************************************************
	> File Name: 3-3.client.c
	> Author: 
	> Mail: 
	> Created Time: Mon 17 Aug 2020 02:08:27 PM CST
 ************************************************************************/

#include "head.h"
#include "common.h"
#include "./usr/user.h"

int sockfd;

void *thread_send(void *arg) {
    struct ChatMsg c_msg;

    while (1) {
        memset(&c_msg, 0, sizeof(c_msg));
        char buff[512] = {0};
        scanf("%[^\n]s", buff);
        getchar();

        deal_send_message(buff, &c_msg);
        printf("%x\n", c_msg.type);
        send(sockfd, &c_msg, sizeof(c_msg), 0);
        DBG(RED"client send message: "NONE"%s\n", c_msg.msg);
    }
}

void *thread_recv(void *arg) {
    struct ChatMsg c_msg;
    memset(&c_msg, 0, sizeof(c_msg));

    while (1) {
        memset(&c_msg, 0, sizeof(c_msg));
        recv(sockfd, &c_msg, sizeof(c_msg), 0);
        DBG(BLUE"client recv message: "NONE"%s\n", c_msg.msg);
        deal_recv_message(&c_msg, sockfd);
    }
}

void deal_send_message(char *buff, struct ChatMsg *c_msg) {

    if (buff[0] == '#') {
        if (buff[1] == '1') {
            printf("check number of people\n");
            c_msg->opt |= FUNC_CHECK_ONLINE; 
        }
        if (buff[1] == '2') {
            printf("change to anonymous identity\n");
            c_msg->opt |= FUNC_CHANGE_NAME; 
        }
    } else if (buff[0] == '@') {
        int ind = 1;
        c_msg->type |= CHAT_PRI;
        while (buff[ind] != ' ') ind++;
        strncpy(c_msg->name, buff + 1, ind - 1);
        strcpy(c_msg->msg, buff + ind + 1);
    } else {
        DBG(RED"client send type: "NONE"pub\n");
        c_msg->type |= CHAT_PUB;
        strcpy(c_msg->msg, buff);
    }
}

void deal_recv_message(struct ChatMsg *c_msg, int fd) {
    if (c_msg->type & CHAT_HEART) {
        DBG(BLUE"client recv type: "NONE"heart\n");
        printf("%s\n", c_msg->msg);
        memset(c_msg, 0, sizeof(struct ChatMsg));
        c_msg->type |= CHAT_ACK;
        strcpy(c_msg->msg, "I feel your heart.");
        printf("%x\n", c_msg->type);
        int nsend = send(fd, &c_msg, sizeof(c_msg), 0);
        printf("nsend = %d, sizeof(c_msg) = %ld\n", nsend, sizeof(c_msg));
        DBG(RED"client send heart: "NONE"%s\n", c_msg->msg);
        
    } else if (c_msg->type & CHAT_FIN_1) {
        DBG(BLUE"client recv type: "NONE"fin_1\n");
        exit(0);
    } else if (c_msg->type & CHAT_FIN) {
        DBG(BLUE"client recv type: "NONE"fin\n");
        memset(c_msg, 0, sizeof(struct ChatMsg));
        c_msg->type |= CHAT_FIN_1;
        send(fd, &c_msg, sizeof(c_msg), 0);
        exit(0);
    }
}

void logout(int signum) {
    printf("recv logout signal!\n");
    struct ChatMsg c_fin;
    memset(&c_fin, 0, sizeof(c_fin));
    c_fin.type |= CHAT_FIN;
    send(sockfd, &c_fin, sizeof(c_fin), 0);
}

int main(int argc, char **argv) {
    int port;
    char ip[20] = {0};
    char name[20] = {0};
    char *tmp;
    if (argc == 1){
        tmp = get_conf("./user_conf", "SERVERIP");
        strcpy(ip, tmp);
        tmp = get_conf("./user_conf", "SERVERPORT");
        port = atoi(tmp);
        tmp = get_conf("./user_conf", "name");
        strcpy(name, tmp);
    } else if (argc == 7){
        int opt;
        while ((opt = getopt(argc, argv, "h:p:n:"))  != -1) {
            switch (opt) {
                case 'h':
                    strcpy(ip, optarg);
                    break;
                case 'p':
                    port = atoi(optarg);
                    break;
                case 'n':
                    strcpy(name, optarg);
                    break;
                default:
                    fprintf(stderr, "Usage : %s ip port name!\n", argv[0]);
                    exit(1);
            }
        }
    } else {
        fprintf(stderr, "Usage : %s ip port name!\n", argv[0]);
        exit(1);
    }
    if ((sockfd = socket_connect(ip, port)) < 0) {
        perror("socket_connect");
        exit(1);
    }

    struct ChatMsg c_syn;
    memset(&c_syn, 0, sizeof(c_syn));
    c_syn.type |= CHAT_SYN;
    strcpy(c_syn.name, name);
  
    if (send(sockfd, &c_syn, sizeof(c_syn), 0) == -1) {
        perror("send()");
    }

    memset(&c_syn, 0, sizeof(c_syn));

    if (recv(sockfd, &c_syn, sizeof(c_syn), 0) == -1) {
        perror("recv()");
    }

    if (c_syn.type & CHAT_NAK) {
        printf("%s , %s\n", c_syn.name, c_syn.msg);
        printf("qaq\n");
        exit(1);
    } else if (c_syn.type & CHAT_ACK) {
        printf("hello %s , %s\n", c_syn.name, c_syn.msg);
    }

    signal(SIGINT, logout);
    
    pthread_t s_tid, r_tid;

    pthread_create(&s_tid, NULL, thread_send, NULL);
    pthread_create(&r_tid, NULL, thread_recv, NULL);


    pthread_join(s_tid, NULL);
    pthread_join(r_tid, NULL);

    return 0;
}
