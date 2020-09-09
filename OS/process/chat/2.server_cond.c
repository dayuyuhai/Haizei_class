/*************************************************************************
	> File Name: server.c
	> Author: 
	> Mail: 
	> Created Time: Sun 02 Aug 2020 07:16:28 PM CST
 ************************************************************************/

#include"head.h"

struct Message {
    char name[20];
    char msg[1024];
    pthread_cond_t cond;
    pthread_mutex_t mutex;
};

struct Message *share_memory = NULL;

int main(int argc, char** argv) {
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

    memset(share_memory, 0, sizeof(struct Message));

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&share_memory->mutex, &attr);

    pthread_condattr_t cond_attr;
    pthread_condattr_init(&cond_attr);
    pthread_condattr_setpshared(&cond_attr, PTHREAD_PROCESS_SHARED);
    pthread_cond_init(&share_memory->cond, &cond_attr);

    while (1) {
        pthread_mutex_lock(&share_memory->mutex);
        pthread_cond_wait(&share_memory->cond, &share_memory->mutex);
        printf("%s : %s\n", share_memory->name, share_memory->msg);
        memset(share_memory->name, 0, sizeof(share_memory->name));
        memset(share_memory->msg, 0, sizeof(share_memory->msg));
        pthread_mutex_unlock(&share_memory->mutex);
    }
    return 0;
}


