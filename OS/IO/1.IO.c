/*************************************************************************
	> File Name: 1.IO.c
	> Author: 
	> Mail: 
	> Created Time: Sat 08 Aug 2020 02:23:18 PM CST
 ************************************************************************/

#include "head.h"
#include "common.h"

int main() {

    make_non_block(1);
    // 或就是加，它们俩的1都有了
    char buff[512] = {0};
    scanf("%s", buff);
    printf("%s\n", buff);

    memset(buff, 0, sizeof(buff));

    make_block(1);
    scanf("%s", buff);
    printf("%s\n", buff);

    return 0;
}
