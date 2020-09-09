/*************************************************************************
	> File Name: thread_pool.c
	> Author: 
	> Mail: 
	> Created Time: Fri 14 Aug 2020 04:56:33 PM CST
 ************************************************************************/

#include "head.h"

extern int epollfd; 
extern int maxfd;
extern struct User user[MAXUSER];
extern struct User *users;
extern int cnt_online;

void send_all(struct ChatMsg *msg) {
    for (int i = 1; i <= maxfd; i++) {
        if (users[i].online == 1) {
            send(users[i].fd, (void *)&msg, sizeof(msg), 0);
        }
    }
}

void send_to(struct User *user, struct ChatMsg *msg) {
    char name[20] = {0};
    int i = 1, send_error_flag = 0;
    for (; i < 22; i++) {
        if (msg->msg[i] == ' ') break;
    }
    if (msg->msg[0] != '@' || msg->msg[i] != ' ') {
        send_error_flag = 1;
        memset(msg, 0, sizeof(msg));
        sprintf(msg->msg, "wrong format");
    } else {
        strncpy(name, msg->msg + 1, i - 1);
        strcpy(msg->msg, &msg->msg[i + 1]);
        int fd = judge_online(users, name, maxfd);
        if (fd > 0) {
            msg->type = CHAT_PRI;
            DBG(GRAY"Chat Pri"NONE" : %s send a msg to %s success\n", user->name, name);
            send(fd, (void *)&msg, sizeof(msg), 0);
        } else {
            send_error_flag = 1;
            memset(msg, 0, sizeof(msg));
            sprintf(msg->msg, "target user is not online");
            DBG(GRAY"Chat Pri"NONE" : %s send a msg to %s failed\n", user->name, name);
        }

    }
    if (send_error_flag) {
        msg->type = CHAT_SYS;
        send(user->fd, (void *)&msg, sizeof(msg), 0);
    }
}

void get_name(int fd) {
    struct ChatMsg msg;
    memset(&msg, 0, sizeof(msg));
    msg.type = CHAT_FUNC;
    msg.opt = FUNC_CHECK_ONLINE;
    int cnt = 0;
    for (int i = 1; i <= maxfd; i++) {
        if (cnt > 10) break;
        if (users[i].online == 1) {
            strcat(msg.msg, users[i].chat_name);             
            msg.msg[strlen(msg.msg)]  = ','; 
            cnt++;
        }
    }   
    msg.msg[strlen(msg.msg) - 1]  = ' '; 
    char tmp[100] = {0};
    sprintf(tmp, "等%d位好友在线先", cnt_online);
    strcat(msg.msg, tmp);             
    printf(RED"msg = %s"NONE, msg.msg);
    send(fd, (void *)&msg, sizeof(msg), 0);
}

void do_work(struct User *user) {
    struct ChatMsg msg;
    /*
    if (recv(user->fd, &msg, sizeof(msg), 0) <= 0) {
        DBG(L_PURPLE"thread_poll"NONE" : %s closed connection abnoramlly\n", user->chat_name);
        del_event(epollfd, user);
        cnt_online--;
        close(user->fd);
        return ;
    }
    */
    recv(user->fd, &msg, sizeof(msg), 0);
    user->flag = 10;
    if (msg.type & CHAT_PUB) {
        strcpy(msg.name, user->chat_name);
        send_all(&msg);
        printf(BLUE"%s"NONE" : %s\n", user->chat_name, msg.msg);
    } else if (msg.type & CHAT_PRI) {
        strcpy(msg.name, user->chat_name);
        send_to(user, &msg);
        printf(GRAY"%s"NONE" : %s\n", user->chat_name, msg.msg);
    } else if (msg.type & CHAT_FUNC) {
        if (msg.msg[0] != '#') {
            sprintf(msg.msg, "请使用# + 数字的形式使用聊天室功能");
            msg.type = CHAT_SYS;
            send(user->fd, (void *)&msg, sizeof(msg), 0);
        } else if (msg.opt & FUNC_CHECK_ONLINE) {
            get_name(user->fd);
        } else if (msg.opt & FUNC_CHANGE_NAME) {
            strcpy(user->chat_name, user->name);
        }
    } else if (msg.type & CHAT_SYN) {
        do_login(user, &msg);
    } else if (msg.type & CHAT_FIN) {
        DBG(L_PURPLE"Chat Fin"NONE" : recv a CHAT_FIN from %s\n", user->chat_name);
        msg.type = CHAT_FIN_1;
        send(user->fd, (void *)&msg, sizeof(msg), 0);
        DBG(L_PURPLE"Chat Fin"NONE" : send a CHAT_FIN to %s\n", user->chat_name);
        close(user->fd);
        user->online = 0;
        del_event(epollfd, user);
        cnt_online--;
    }
}

void task_queue_init(struct task_queue *taskQueue, int size, int epollfd) {
    taskQueue->size = size;
    taskQueue->epollfd = epollfd;
    taskQueue->total = taskQueue->head = taskQueue->tail = 0;
    taskQueue->users = calloc(size, sizeof(struct User));
    pthread_mutex_init(&taskQueue->mutex, NULL);
    pthread_cond_init(&taskQueue->cond, NULL);
    return ;
}

void task_queue_push(struct task_queue *taskQueue, struct User *user) {
    pthread_mutex_lock(&taskQueue->mutex);
    if (taskQueue->total == taskQueue->size) {
        pthread_mutex_unlock(&taskQueue->mutex);
        DBG(YELLOW"<taskQueue>"NONE" : taskQueue is full!\n");
        return;
    }
    taskQueue->users[taskQueue->tail] = user;
    taskQueue->total++;
    DBG(GREEN"<Push>"NONE" : %s\n", user->name);
    if (++taskQueue->tail == taskQueue->size) {
        DBG(RED"<taskQueue>"NONE" : End\n");
        taskQueue->tail = 0;
    }
    pthread_cond_signal(&taskQueue->cond);
    pthread_mutex_unlock(&taskQueue->mutex);
}

struct User *task_queue_pop(struct task_queue *taskQueue) {
    pthread_mutex_lock(&taskQueue->mutex);
    while (taskQueue->total == 0) {
        DBG(PURPLE"<Debug>"NONE" : taskQueue is empty!\n ");
        pthread_cond_wait(&taskQueue->cond, &taskQueue->mutex);
    }
    struct User *user = taskQueue->users[taskQueue->head];
    taskQueue->total--;
    DBG(BLUE"<taskQueue>"NONE" : pop %d!\n", user->fd);
    if (++taskQueue->head == taskQueue->size) {
        taskQueue->head = 0;
    }
   // sleep(1);
    pthread_mutex_unlock(&taskQueue->mutex);
    return user;
}

void *thread_run(void *arg) {
    pthread_detach(pthread_self());
    struct task_queue *taskQueue = (struct task_queue *)arg;
    while (1) {
        struct User *user = task_queue_pop(taskQueue);
        do_work(user);
    }
}
