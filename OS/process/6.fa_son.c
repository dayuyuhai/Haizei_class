/*************************************************************************
	> File Name: 6.fa_son.c
	> Author: 
	> Mail: 
	> Created Time: Sun 02 Aug 2020 04:31:48 PM CST
 ************************************************************************/

#include "head.h"

struct Str {
    char s[512];
    pthread_mutex_t mutex;
};

struct Str *share_memory = NULL;

void output() {
    while (1) {
        if (strlen(share_memory->s)) {
            pthread_mutex_lock(&share_memory->mutex);
            printf("%s\n", share_memory->s);
            memset(share_memory->s, 0, sizeof(share_memory->s));
            pthread_mutex_unlock(&share_memory->mutex);
        }
    }
}

int main() {
    pid_t pid;
    int shmid;
    key_t key = ftok(".", 2010);
    if ((shmid = shmget(key, sizeof(struct Str), IPC_CREAT | 0666)) < 0) {
        perror("shmget()");
        exit(1);
    }

    if ((share_memory = (struct Str *)shmat(shmid, NULL, 0)) == NULL) {
        perror("shmat()");
        exit(1);
    }
    
    memset(share_memory, 0, sizeof(struct Str));
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
            if (strlen(share_memory->s)) continue;
            pthread_mutex_lock(&share_memory->mutex);
            scanf("%s", share_memory->s);
            getchar();
            pthread_mutex_unlock(&share_memory->mutex);
        }
    } else {
        output();
        wait(NULL);
    }


    return 0;
}
