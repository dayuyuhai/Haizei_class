/*************************************************************************
	> File Name: 3.multi_thread_add.c
	> Author: 
	> Mail: 
	> Created Time: Sat 01 Aug 2020 06:49:13 PM CST
 ************************************************************************/

#include"head.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int sum = 0, now = 0;

void *add(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);
        if (now >= 1000) {
            pthread_mutex_unlock(&mutex);
            break;
        }
        now++;
        sum += now;
        pthread_mutex_unlock(&mutex);
        printf("<%ld> : %d\n", pthread_self(), now);
        usleep(20);
    }
}


int main() {
    pthread_t tid[5];
    for (int i = 0; i < 5; i++) {
        pthread_create(&tid[i], NULL, add, NULL);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(tid[i], NULL);
    }
    printf("sum = %d\n", sum);

    return 0;
}
