/*************************************************************************
	> File Name: 1.m_inet_ntoa.c
	> Author: 
	> Mail: 
	> Created Time: Thu 17 Sep 2020 07:24:17 AM CST
 ************************************************************************/

#include<stdio.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<inttypes.h>

char *my_inet_ntoa(struct in_addr in) {
    static char ip[20] = {0};
    uint8_t *p;
    p = (uint8_t *)&in.s_addr;
    sprintf(ip, "%d.%d.%d.%d\n", p[0], p[1], p[2], p[3]);
    return ip;
}

int main() {
    char input_ip[20] = {0};
    scanf("%s", input_ip);
    printf("input_ip = %s\n", input_ip);
    printf("uint32_t ip = %d\n", inet_addr(input_ip));
    struct in_addr in;
    in.s_addr = inet_addr(input_ip);
    printf("Ip After Change: %s\n", my_inet_ntoa(in));

    return 0;
}

