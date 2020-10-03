/*************************************************************************
	> File Name: 判断大小端.c
	> Author: 
	> Mail: 
	> Created Time: Thu 17 Sep 2020 07:08:56 AM CST
 ************************************************************************/

#include<stdio.h>

int main() {
    int a = 1;
    if (*(char *)&a == 1) {
        printf("小端！\n");
    } else {
        printf("大端！\n");
    }
    return 0;
}
