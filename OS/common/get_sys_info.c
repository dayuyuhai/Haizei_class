/*************************************************************************
	> File Name: get_sys_info.c
	> Author: 
	> Mail: 
	> Created Time: Wed 21 Oct 2020 07:24:38 AM CST
 ************************************************************************/

#include "head.h"

void *disk(void *arg) {
    int blinking = get_json_valueint((cJSON *)arg, "Timer", "Disk");
    while (1) {
        sleep(blinking);
        printf("blinking = %d\n", blinking);
        system("bash /home/syl/Haizei_class/OS/shell/1-2.disk.sh >> InfoLog/1.dish.log");
    }
}



void *memory(void *arg) {
    int blinking = get_json_valueint((cJSON *)arg, "Timer", "Mem");
    while (1) {
        sleep(blinking);
        printf("blinking = %d\n", blinking);
        system("bash /home/syl/Haizei_class/OS/shell/2-2.memory.sh >> InfoLog/2.mem.log");
    }
}

void *CPU(void *arg) {
    int blinking = get_json_valueint((cJSON *)arg, "Timer", "Cpu");
    while (1) {
        sleep(blinking);
        printf("blinking = %d\n", blinking);
        system("bash /home/syl/Haizei_class/OS/shell/3-2.CPU.sh >> InfoLog/3.cpu.log");
    }
    
}

void *sys(void *arg) {
    int blinking = get_json_valueint((cJSON *)arg, "Timer", "Sysinfo");
    while (1) {
        sleep(blinking);
        printf("blinking = %d\n", blinking);
        system("bash /home/syl/Haizei_class/OS/shell/4-2.sys.sh >> InfoLog/4.sys.log");
    }
    
}
void *user(void *arg) {
    int blinking = get_json_valueint((cJSON *)arg, "Timer", "User");
    while (1) {
        sleep(blinking);
        printf("blinking = %d\n", blinking);
        system("bash /home/syl/Haizei_class/OS/shell/5.user.sh >> InfoLog/5.user.log");
    }
    
}

void *bad_process(void *arg) {
    int blinking = get_json_valueint((cJSON *)arg, "Timer", "Proc");
    while (1) {
        sleep(blinking);
        printf("blinking = %d\n", blinking);
        system("bash /home/syl/Haizei_class/OS/shell/6-2.bad_process.sh >> InfoLog/6.pro.log");
    }
    
}


