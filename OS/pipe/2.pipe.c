/*************************************************************************
	> File Name: 2.pipe.c
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Aug 2020 02:16:36 PM CST
 ************************************************************************/

#include<stdio.h>
#include"head.h"
#define BUFFSIZE 512

int main(int argc, char **argv) {
    FILE *fp;
    char buff[BUFFSIZE + 5] = {0};
    if ((fp = popen("ls /etc", "r")) == NULL) {
        perror("popen()");
        exit(1);
    }
    
    while (fread(buff, 1, BUFFSIZE, fp) > 0) {
        printf("%s", buff);
        memset(buff, 0, sizeof(buff));
    }
    pclose(fp);
    return 0;
}
