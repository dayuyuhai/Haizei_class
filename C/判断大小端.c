/*************************************************************************
	> File Name: 判断大小端.c
	> Author: 
	> Mail: 
	> Created Time: Thu 17 Sep 2020 07:08:56 AM CST
 ************************************************************************/

#include<stdio.h>

union Data {
    int a;
    char b[4];  // char b 也可以 内存从低地址分配
};

int main() {
    union Data data;
    data.a = 1;
    if (data.b[0] == 1) {
        printf("小端！\n");
    } else {
        printf("大端！\n");
    }
    return 0;
}
