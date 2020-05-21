/*************************************************************************
	> File Name: main.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Thu 21 May 2020 08:45:56 PM CST
 ************************************************************************/

#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

void output(int argc, char *argv[], char *env[]) {
	for (int i = 0; i < argc; i++) {
		printf("%s\n", argv[i]);
	}
	for (int i = 0; env[i]; i++) {
		if (strncmp(env[i], "USER=", 5) == 0) {
			if (strncmp(env[i] + 5, "zyt", sizeof(env[i]) == 0)) {
				printf("welcome meinv\n");
			} else {
				printf("get out!!!\n");
				exit(0);
			}
		}
	}
	return ;
}

int main(int argc, char *argv[], char *env[]) {
	output(argc, argv, env);
	return 0;
}
