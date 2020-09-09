/*************************************************************************
	> File Name: 6.fa_son.c
	> Author: 
	> Mail: 
	> Created Time: Sun 02 Aug 2020 04:31:48 PM CST
 ************************************************************************/

#include "head.h"

struct Str {
    char s[512];
};

struct Str *share_memory = NULL;

void *output(int signum) {
    printf("%s", share_memory->s);
    memset(share_memory->s, 0, sizeof(share_memory->s));
    return NULL;
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

    if ((pid = fork()) < 0) {
        perror("fork()");
        exit(1);
    }

    if (pid == 0) {
        while (1) {
            printf("Please input:");
            scanf("%[^\n]s", share_memory->s);
            getchar();
            kill(getppid(), SIGUSR1);
        }
    } else {
        signal(SIGUSR1, output);
        wait(NULL);
    }


    return 0;
}
