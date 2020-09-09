/*************************************************************************
	> File Name: b.c
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 16 Jun 2020 08:17:01 PM CST
 ************************************************************************/

#include <stdio.h>

#define cb(X) _Generic((X), \
    int : "%d" \
)

int main()  {
    int a = 23;
    printf(cb(a), a);
	return 0;
}
