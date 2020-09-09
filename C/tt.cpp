/*************************************************************************
	> File Name: tt.cpp
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 19 May 2020 08:17:42 PM CST
 ************************************************************************/

#include<iostream>
using namespace std;

int main() {
	static int a = 123;
	static int b = 128;
	printf("%d\n", ((char*)&a[0]));
	printf("%d\n", ((char*)&b[0 ]))
	return 0;
}
