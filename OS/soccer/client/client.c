/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Fri 23 Oct 2020 06:24:45 PM CST
 ************************************************************************/

#include "head.h"

char *conf = "./football.conf";
int server_port;
char server_ip[20] = {0};
char name[20] = {0};
int team = -1;
char msg[512] = {0};
int sockfd = -1;

int main(int argc, char **argv) {
    int opt;
    struct LogRequest request;
    struct LogResponse response;

    bzero(&request, sizeof(request));
    bzero(&response, sizeof(response));

    while ((opt = getopt(argc, argv, "h:p:n:t:m:"))  != -1) {
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
            case 't':
                team = atoi(optarg);
                break;
            case 'm':
                strcpy(msg, optarg);
                break;
            default:
                fprintf(stderr, "Usage : %s ip port name team_num message!\n", argv[0]);
                exit(1);
        }
    }


    if (!server_port) server_port = atoi(get_conf(conf, "SERVERPORT"));
    if (!strlen(server_ip)) strcpy(server_ip, get_conf(conf, "SERVERIP"));
    if (!strlen(name)) strcpy(name, get_conf(conf, "NAME"));
    if (team < 0) team = atoi(get_conf(conf, "TEAM"));
    if (!strlen(msg)) strcpy(msg, get_conf(conf, "MSG"));
    
    strcpy(request.name, name);
    strcpy(request.msg, msg);
    request.team = team;

    if ((sockfd = socket_udp()) == -1) {
        perror("socket_udp");
        exit(1);
    } 

    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(server_port);
    server.sin_addr.s_addr = inet_addr(server_ip);
    socklen_t len = sizeof(server);

    sendto(sockfd, (void *)&request, sizeof(request), 0, (struct sockaddr *)&server, sizeof(server));

    fd_set read;
    FD_ZERO(&read);
    FD_SET(sockfd, &read);
    struct timeval timeout;
    timeout.tv_sec = 5;
    int retval = select(1, &read, NULL, NULL, &timeout);

    if (retval < 0) {
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

    printf("Server : %s\n", response.msg);
    connect(sockfd, (struct sockaddr *)&server, len);

    //是否需要更多的逻辑或者数据传输来测试，请自己决定，如果需要，在服务端，应该用多线程


    return 0;
}
