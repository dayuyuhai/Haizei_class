/*************************************************************************
	> File Name: 3.test.cpp
	> Author: 
	> Mail: 
	> Created Time: Tue 19 Jan 2021 08:01:40 PM CST
 ************************************************************************/

#include<stdio.h>
#include<string.h>
int main(void)
{
    char str[] = "\0";
    printf("sizeof str is %ld,string len is %ld\n",sizeof(str),strlen(str));
    return 0;
}
