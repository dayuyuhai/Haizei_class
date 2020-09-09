/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Tue 04 Aug 2020 03:26:50 PM CST
 ************************************************************************/

#include"head.h"
#include"popen.h"

int main() {
    FILE *fp;
    char buff[1024] = {0};
    if ((fp = m_popen("ls /etc", "r")) == NULL) {
        perror("m_popen()");
        exit(1);
    }
    while (fgets(buff, sizeof(buff), fp) != NULL) {
        printf("%s", buff);
        bzero(buff, sizeof(buff));
    }
    int status = m_pclose(fp);

    printf("status = %d\n", status);

    return 0;
}
