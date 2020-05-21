/*************************************************************************
	> File Name: maco.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Thu 21 May 2020 08:41:46 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#define pchar char *
typedef char * ppchar;

int main() {
	pchar p, q;
	ppchar a, b;
	printf("p = %lu, q = %lu\n", sizeof(p), sizeof(q));
	printf("a = %lu, b = %lu\n", sizeof(a), sizeof(b));
	return 0;
}
