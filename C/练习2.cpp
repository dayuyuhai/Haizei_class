/*************************************************************************
	> File Name: 练习2.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Thu 14 May 2020 08:15:00 PM CST
 ************************************************************************/

#include<iostream>
#ifdef DEBUG
using namespace std;
#define log(frm, args...) { \
	printf("[%s : %d] %s ", __func__, __LINE__, #args); \
	printf(frm, ##args);  \
	printf("\n"); \
}
// #将当前变量转换成字符串
// ##连接 将frm和args连成一个东西处理,就能支持参数为0
//下面用abcdef测试一下
#else
#define log(frm, arg...) 
#endif

#define contact(a, b) a##b

int main() {
	int a = 3, abc, def;
	int abcdef = 0;
	log("%d", abcdef);
	log("%d", a);
	log("hello world");
	contact(abc, def) = 123;
	log("%d", abcdef);
	return 0;
}
