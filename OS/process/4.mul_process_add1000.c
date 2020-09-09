/*************************************************************************
	> File Name: 4.mul_process_add1000.c
	> Author: 
	> Mail: 
	> Created Time: Sat 01 Aug 2020 08:14:41 PM CST
 ************************************************************************/

#include"head.h"

int sum = 0, now = 0;

struct Num {
    int now;
    int sum;
};

char lock_file[] = "./.lock";
char num_file[] = "./.num";

size_t set_num(struct Num *num) {
    FILE *f = fopen(num_file, "w");
    size_t nwrite = fwrite(num, sizeof(struct Num), 1, f);
    fclose(f);
    return nwrite;
}

size_t get_num(struct Num *num) {
    FILE *f = fopen(num_file, "r");
    // 文件不存在，写会打开一个，读不会
    if (f == NULL) {
        fclose(f);
        perror("fopen_r()");
        return -1;
    }
    size_t nread = fread(num, sizeof(struct Num), 1, f);
    if (nread < 0) {
        fclose(f);
        return -1;
    }
    fclose(f);
    return nread;
}

void add(int max, int x) {
    struct Num num;
    while (1) {
        FILE *lock = fopen(lock_file, "w");
        flock(lock->_fileno, LOCK_EX);
        if (get_num(&num) < 0) {
            fclose(lock);   // 关闭文件，锁也关
            continue;
        }
        // printf("<%d> now = %d, sum = %d\n", x, num.now, num.sum);
        // DBG(GREEN"<Debug>"NONE" : <%d> now = %d sum = %d\n". x. num.now, num.sum);
        if (num.now > max) {
            // printf("%d out\n", x);
            fclose(lock);
            break;
        }
        num.sum += num.now;
        (num.now)++;
        set_num(&num);
        flock(lock->_fileno, LOCK_UN);
        fclose(lock);
    }
}


int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage : %s max ins\n", argv[0]);
        exit(1);
    }
    int max = atoi(argv[1]);
    int ins = atoi(argv[2]);
    struct Num num;
    num.now = 0;
    num.sum = 0;

    set_num(&num);

    pid_t pid;
    int x = 0;
    for (int i = 0; i < ins; i++) {
        if ((pid = fork()) < 0) {
            perror("fork()");
            exit(1);
        }
        x = i;
        if (pid == 0) {
            // printf("%d ready\n", x);
            break;

    }}
    if (pid == 0) {
        // printf("%d work\n", x);
        add(max, x);
        // printf("%d exit\n", x);
        exit(0);
    }
    
    while (ins--) {
        wait(NULL);
    }

    get_num(&num);

    printf("sum = %d\n", num.sum);

    return 0;
}

