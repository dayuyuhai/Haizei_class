/*************************************************************************
	> File Name: name_90-9.cpp
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2020年05月09日 星期六 14时45分57秒
 ************************************************************************/

#include<iostream>
#include<time.h>
using namespace std;
#define max_n 16

char name[max_n][20] = {"杨宇晨", "严志伟", "何进康", "刘雨欣", "吴根胜",
	"周缘", "张晓宇", "张本超", "张芝涵", "张雨桐", "曹政", "樊帅朋",
	"艾艺", "郑佳伟", "魏嘉锐", "黄啸峰"};

int flag[max_n] = {0};
void output_name(int n) {
	srand(time(0));
	for (int i = 0; i < n;) {
		int index = rand() % max_n;
		if (flag[index]) continue;
		printf("%s ", name[index]);
		flag[index] = 1, i++;
	}
	printf("\n");
	return ;
}

int str_to_int(char *str) {
	int cnt = 0;
	for (int i = 0; str[i]; i++) {
		cnt = cnt * 10 + str[i] - '0';
	}
	return cnt;
}

int main(int argc, char *argv[]) {
	char str[3] = {0};
	if (argc < 2) {
		output_name(1);
	} else {
		sprintf(str, "%s", argv[1]);
		int n = str_to_int(str);
		if (n > max_n) {
			printf("最多%d个\n", max_n);
			exit(0);
		}
		output_name(n);
	}
	return 0;
}
