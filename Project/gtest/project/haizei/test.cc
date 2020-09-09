#include<haizei/gtest.h>
#include<string.h>
#include<stdio.h>

int test_func_cnt = 0;
int cnt = 0, cnt_success = 0;

Function test_func_arr[100];


int RUN_ALL_TESTS() {
	for (int i = 0; i < test_func_cnt; i++) {
		printf("\033[40;32m[====RUN====]\033[0m \033[40;31m%s\033[0m\n", test_func_arr[i].name);
		cnt = 0;
		cnt_success = 0;
		test_func_arr[i].func();
		if (cnt == cnt_success) {
		printf("\033[40;32m[\033[0m\033[40;34m%8.2lf%%  \033[0m\033[40;32m]\033[0m total : %d  success : %d\n", 1.0 * cnt_success / cnt * 100, cnt, cnt_success);
		} else {
		printf("\033[40;32m[\033[0m\033[40;31m%8.2lf%%  \033[0m\033[40;32m]\033[0m total : %d  success : %d\n", 1.0 * cnt_success / cnt * 100, cnt, cnt_success);
		}
	}
	return 0;
}

void add_func(funcp func, const char *str) {
	test_func_arr[test_func_cnt].func = func; 
	test_func_arr[test_func_cnt].name = strdup(str); 
	test_func_cnt++;
	return ;
}
