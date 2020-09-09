/*************************************************************************
	> File Name: 7.随堂4.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Sat 16 May 2020 03:04:35 PM CST
 ************************************************************************/

#include<iostream>
#include<string.h>
using namespace std;

int main() {
	char str[10] = {0};
	int n;
	while (~scanf("%d", &n)) {
		sprintf(str, "%x", n);	
		printf("%lu\n", strlen(str));
	}
	return 0;
}
