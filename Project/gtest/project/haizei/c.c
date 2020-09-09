/*************************************************************************
	> File Name: c.c
	> Author: 北海望谷堆
	> Mail: dayuyuhai@outlook.com 
	> Created Time: Tue 16 Jun 2020 09:29:42 PM CST
 ************************************************************************/

#include <stdio.h>
#include<math.h>
// tgmath.h 宏 cbrt 的可能实现
#define cc(X) _Generic((X), \
    double: cbrtf  \
)(X)
 
int main(void)
{
    double x = 8.0;
    printf("%f\n", cc(x)); 
}
