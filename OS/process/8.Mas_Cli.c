/*************************************************************************
	> File Name: Mas_Cli.c
	> Author: 
	> Mail: 
	> Created Time: Sun 11 Oct 2020 02:41:42 PM CST
 ************************************************************************/

#include "head.h"


struct Num {
    int status;
    pthread_mutex_t mutex;
};

struct Num *share_memory = NULL;

void output1(int signum) {
    printf("change to client\n");
    pthread_mutex_lock(&share_memory->mutex);
    return ;
}

void output2(int signum) {
    printf("change to master\n");
    pthread_mutex_lock(&share_memory->mutex);
    return ;
}
int main() {
    pid_t pid;

    int shmid;
    key_t key = ftok(".", 2023);
    if ((shmid = shmget(key, sizeof(struct Num), IPC_CREAT | 0666)) < 0) {
        perror("shmget()");
        exit(1);
    }

    if ((share_memory = (struct Num*)shmat(shmid, NULL, 0)) == NULL) {
        perror("shmat()");
        exit(1);
    }


    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&share_memory->mutex, &attr);

    if ((pid = fork()) < 0) {
        perror("fork()");
        exit(1);
    }

    if (pid == 0) {
        while (1) {
            signal(SIGUSR1, output1);
            printf("I'm Client\n");
            printf("lock in client\n");
            scanf("%d", &share_memory->status);
            if (share_memory->status == 1) {
                pthread_mutex_unlock(&share_memory->mutex);
                printf("unlock, to master\n");
                kill(getppid(), SIGUSR2);
            } else {
                pthread_mutex_unlock(&share_memory->mutex);
                printf("unlock\n");
            }
        }
    } else {
        while (1) {
            signal(SIGUSR2, output2);
            printf("I'm Master\n");
            printf("lock in master\n");
            scanf("%d", &share_memory->status);
            if (share_memory->status == 2) {
                pthread_mutex_unlock(&share_memory->mutex);
                printf("unlock, to client\n");
                kill(pid, SIGUSR1);
            } else {
                pthread_mutex_unlock(&share_memory->mutex);
                printf("unlock\n");
            }
        }
    }


    return 0;
}

