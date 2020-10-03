/*************************************************************************
	> File Name: 2.umbrella.c
	> Author: 
	> Mail: 
	> Created Time: Wed 23 Sep 2020 10:29:48 PM CST
 ************************************************************************/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>


union  semun {
    int val;
} um;


#define handle_error(msg) \
           do { perror(msg); exit(EXIT_FAILURE); } while (0)

void process(int semid, int x, struct sembuf *P, struct sembuf *V) {
    int semval;
    srand(time(0));
    for (int i = 0; i < 3;) {
        sleep(1);
        int out_flag = rand() % 2;
        if (out_flag == 1) {
            semop(semid, P, 1);

            /*
            if ((semval = semctl(semid, 0, GETVAL, um)) == -1) {
                handle_error("semctl");
            }
            */
            printf("No.%d takes\n", x);
            // printf("No.%d takes, %d left\n", x, semval);
            int time = rand() % 5;
            sleep(time);
            printf("No.%d back \n", x);

            semop(semid, V, 1);
            i++;
        }

    }
}

int main() {
    int num_of_people = 6;
    pid_t pid;
    int x = 0, semid;
    key_t key = ftok(".", 2014);
    if ((semid = semget(key, 1, IPC_CREAT | 0777)) == -1) {
        handle_error("semget");
    }

    struct sembuf P = {0, -1, SEM_UNDO};
    struct sembuf V = {0, 1, SEM_UNDO};

//    union semun um;
    um.val = 3;
    if (semctl(semid, 0, SETVAL, um) == -1) {
        handle_error("semctl");
    }

    for (int i = 0; i < num_of_people; i++) {
        if ((pid = fork()) < 0) {
            handle_error("fork()");
        }
        x = i;
        if (pid == 0) {
            break;
        }
    }
    if (pid == 0) {
        process(semid, x, &P, &V);
        exit(0);
    }
    
    while (num_of_people--) {
        wait(NULL);
    }

    return 0;
}
