/*************************************************************************
	> File Name: Mas_Cli.c
	> Author: 
	> Mail: 
	> Created Time: Sun 11 Oct 2020 02:41:42 PM CST
 ************************************************************************/

#include "head.h"


void output1(int signum) {
    printf("I'm Master\n");
    return ;
}

void output2(int signum) {
    printf("I'm Client\n");
    return ;
}

int main() {
    pid_t pid;
    int x, status, pidd[2];
    pthread_mutex_t mutex;

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&mutex, &attr);

    for (int i = 0; i < 2; i++) {
        if ((pid = fork()) < 0) {
            perror("fork()");
            exit(1);
        }
        x = i;
        if (pid == 0) break;
        else pidd[x] = pid;
    }


    if (pid == 0 && x == 0) {
        while (1) {
            pthread_mutex_lock(&mutex);
            signal(SIGUSR1, output1);
            pthread_mutex_unlock(&mutex);
        }
    } else if (pid == 0 && x == 1) {
        while (1) {
            pthread_mutex_lock(&mutex);
            signal(SIGUSR2, output2);
            pthread_mutex_unlock(&mutex);
        }
    } else {
        while (1) {
            scanf("%d", &status);
            if (status == 1) {
                kill(pidd[0], SIGUSR1);
            } else {
                kill(pidd[1], SIGUSR2);
            }
        }
    }


    return 0;
}

