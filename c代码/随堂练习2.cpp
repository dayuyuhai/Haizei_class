/*************************************************************************
	> File Name: 随堂练习2.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Thu 14 May 2020 06:59:57 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;
#define MAX(a, b) ({ \
	__typeof(a) __a = (a); \
	__typeof(b) __b = (b); \
	__a > __b ? __a : __b; \
})

#define P(a) {  \
	printf("%s = %d\n", #a, a); \
}

//#a将a里面的内容以字符串的形式显现出来

//#define MAX(a, b) ((c = (a)), ((c > (b)) ? c : (b)))
//自己打的  问题:不是纯的宏

int main() {
//	int c;
	int a = 7;
	P(MAX(2, 3));
	P(5 + MAX(2, 3));
	P(MAX(2, MAX(3, 4)));
	P(MAX(2, 3 > 4 ? 3 : 4));
	P(MAX(a++, 6));
	P(a);
	return 0;
}
