/*************************************************************************
	> File Name: test.c
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Fri 19 Jun 2020 09:23:26 PM CST
 ************************************************************************/

#include<stdio.h>
#include<haizei/gtest.h>
#include<string.h>

int func_cnt = 0;
int cnt, cnt_success;

struct fun {
	funcp func;
	const char *name;
} func_arr[100];

int RUN_ALL_TESTS() {
	for (int i = 0; i < func_cnt; i++) {
		cnt = cnt_success = 0;
		if (i > 0) printf("\n");
		printf(GREEN_HL("[----RUN----]") RED_HL(" %s\n"), func_arr[i].name);
		func_arr[i].func();

		double rate = 100.0 * cnt_success / cnt;
		printf(GREEN("["));
		if (cnt - cnt_success) printf(RED_HL("%8.2lf%%"), rate);
		else printf(BLUE_HL("%8.2lf%%"), rate);
		printf(GREEN("  ]"));
		printf(" total : %d  success : %d\n", cnt, cnt_success);
		printf("\n");
	}
	return 0;
}

void addfunc(funcp func, const char *name) {
	func_arr[func_cnt].func = func;
	func_arr[func_cnt].name = strdup(name);
	func_cnt++;
	return ;
}
