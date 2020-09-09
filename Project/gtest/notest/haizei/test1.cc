/*************************************************************************
	> File Name: test.c
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Fri 19 Jun 2020 09:23:26 PM CST
 ************************************************************************/

#include<stdio.h>
#include<haizei/gtest.h>

int func_cnt = 0;

struct fun {
	funcp func;
	const char *name;
} func_arr[100];

int RUN_ALL_TESTS() {
	for (int i = 0; i < func_cnt; i++) {
		if (i > 0) printf("\n");
		printf("[----RUN----] %s\n", func_arr[i].name);
		func_arr[i].func();
		printf("[--RUN END--]\n");
	}
	return 0;
}

void addfunc(funcp func, const char *name) {
	func_arr[func_cnt].func = func;
	func_arr[func_cnt].name = name;
	func_cnt++;
}
