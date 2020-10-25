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
    pthread_cond_t cond;
};

struct Num *share_memory = NULL;

int main() {


    pid_t pid;


    make_non_block(1);

    int shmid;
    key_t key = ftok(".", 2025);
    if ((shmid = shmget(key, sizeof(struct Num), IPC_CREAT | 0666)) < 0) {
        perror("shmget()");
        exit(1);
    }

    if ((share_memory = (struct Num*)shmat(shmid, NULL, 0)) == NULL) {
        perror("shmat()");
        exit(1);
    }

    share_memory->status = 2;


    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&share_memory->mutex, &attr);

    pthread_condattr_t c_attr;
    pthread_condattr_init(&c_attr);
    pthread_condattr_setpshared(&c_attr, PTHREAD_PROCESS_SHARED);
    pthread_cond_init(&share_memory->cond, &c_attr);

    DBG(GREEN"Checking config file...\n");

    char buff[512];
    if ((get_string("/home/syl/Haizei_class/OS/分布式/conf.json", buff, sizeof(buff))) < 0) {
        perror("get_string");
        exit(1);
    }
    parse_conf(buff);
    pthread_t tid[6];
    cJSON *conf = get_cjson("time.json");
    cJSON *ob = get_json_valueobject(conf, "Slave");

    if ((pid = fork()) < 0) {
        perror("fork()");
        exit(1);
    }

    if (pid == 0) {
        pthread_create(&tid[0], NULL, disk, (void *)ob);
        pthread_create(&tid[1], NULL, memory, (void *)ob);
        pthread_create(&tid[2], NULL, CPU, (void *)ob);
        pthread_create(&tid[3], NULL, sys, (void *)ob);
        pthread_create(&tid[4], NULL, user, (void *)ob);
        pthread_create(&tid[5], NULL, bad_process, (void *)ob);
        while (1) {
            pthread_mutex_lock(&share_memory->mutex);
            if (share_memory->status == 1) {
                pthread_cond_wait(&share_memory->cond, &share_memory->mutex);
            }
            scanf("%d", &share_memory->status);
            sleep(1);
            if (share_memory->status == 1) {
                printf("unlock, to master\n");
                pthread_mutex_unlock(&share_memory->mutex);
                pthread_cond_signal(&share_memory->cond);
            } else {
                printf("I'm Client\n");
                pthread_mutex_unlock(&share_memory->mutex);
            }
        }
        for (int i = 0; i < 6; i++) {
            pthread_join(tid[i], NULL);
        }

    } else {
        while (1) {
            pthread_mutex_lock(&share_memory->mutex);
            if (share_memory->status == 2) {
                pthread_cond_wait(&share_memory->cond, &share_memory->mutex);
            }
            scanf("%d", &share_memory->status);
            sleep(1);
            if (share_memory->status == 2) {
                printf("unlock, to client\n");
                pthread_mutex_unlock(&share_memory->mutex);
                pthread_cond_signal(&share_memory->cond);
            } else {
                printf("I'm Master\n");
                pthread_mutex_unlock(&share_memory->mutex);
            }
        }
        wait(NULL);
    }

    return 0;
}

