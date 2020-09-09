/*************************************************************************
	> File Name: 2.multi_process.c
	> Author: 
	> Mail: 
	> Created Time: Sat 01 Aug 2020 02:19:37 PM CST
 ************************************************************************/

#include"head.h"

int main(int argc, char **argv) {
    int opt, m_flag = 0;
    char msg[1024] = {0};
    while ((opt = getopt(argc, argv, "m:")) != -1) {
        switch (opt) {
            case 'm':
                m_flag = 1;
                strcpy(msg, optarg);
                break;
            default:
                fprintf(stderr, "Usage : %s -m msg\n", argv[0]);
                exit(1);
        }
    }

    if (m_flag == 1) {
        printf("%s\n", msg);
        return 0;
    }
    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("fork()");
        exit(1);
    }

    if (pid == 0) {
        execlp("vim", "vim", "./tmp.txt", NULL);
    } else {
        wait(NULL);
        execl("/bin/cat", "cat", "./tmp.txt", NULL);
    }
    return 0;
}
