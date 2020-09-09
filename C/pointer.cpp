/*************************************************************************
	> File Name: pointer.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Thu 21 May 2020 07:47:48 PM CST
 ************************************************************************/

#include<iostream>
#define offset(T, a) ((long)(&(((T *)(NULL))->a)))

using namespace std;

struct data {
	int a;
	double b;
	char c;
};

int main() {
	int num = 0x616263;
	int num2 = 0x61626364;
	printf("%s\n", (char*)(&num2));
	printf("%ld\n", offset(struct data, a));
	printf("%ld\n", offset(struct data, b));
	printf("%ld\n", offset(struct data, c));
	return 0;
}
