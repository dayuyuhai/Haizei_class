/*************************************************************************
	> File Name: head.h
	> Author: 
	> Mail: 
	> Created Time: Mon 27 Jul 2020 04:18:58 PM CST
 ************************************************************************/

#ifndef _HEAD_H
#define _HEAD_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <cjson/cJSON.h>
#include "color.h"
#include <errno.h>
#include <sys/epoll.h>
#include <ncurses.h>
#include <signal.h>
#include <locale.h>
#include "common.h"
#include "chat.h"
#include "user.h"
#include "thread_pool.h"
#include "client_func.h"
#include "chat_ui.h"
#include "parse_conf.h"
#include "get_sys_info.h"
#include "4.udp_epoll.h"
#include "4.datatype.h"

#ifdef _D
#define DBG(frm, args...) printf(frm, ##args)
#else
#define DBG(frm, args...) 
#endif


#endif
