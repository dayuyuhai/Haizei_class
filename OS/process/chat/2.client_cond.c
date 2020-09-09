/*************************************************************************
	> File Name: client.c
	> Author: 
	> Mail: 
	> Created Time: Sun 02 Aug 2020 07:25:35 PM CST
 ************************************************************************/

#include<stdio.h>
#include "head.h"

struct Message {
    char name[20];
    char msg[1024];
    pthread_cond_t cond;
    pthread_mutex_t mutex;
};

struct Message *share_memory = NULL;

int main(int argc, char **argv) {
    int opt;
    struct Message tmp;
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
                strcpy(tmp.name, optarg);
                break;
            default:
                fprintf(stderr, "Usage : %s -n name!\n", argv[0]);
                break;
        }
    }
    int shmid;
    key_t key = ftok(".", 2011);
    if ((shmid = shmget(key, sizeof(struct Message), IPC_CREAT | 0666)) < 0) {
        perror("shmget()");
        exit(1);
    }

    if ((share_memory = (struct Message *)shmat(shmid, NULL, 0)) == NULL) {
        perror("shmat()");
        exit(1);
    }

    while (1) { 
        scanf("%[^\n]", tmp.msg);
        getchar();
        if (!strlen(tmp.msg)) continue;
        while (1) {
            if (!strlen(share_memory->msg)) {
                pthread_mutex_lock(&share_memory->mutex);
                break;
            }
        }
        strcpy(share_memory->name, tmp.name);
        strcpy(share_memory->msg, tmp.msg);
        pthread_mutex_unlock(&share_memory->mutex);
        pthread_cond_signal(&share_memory->cond);
        memset(tmp.msg, 0, sizeof(tmp.msg));
    }

    return 0;
}
