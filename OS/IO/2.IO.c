/*************************************************************************
	> File Name: 2.IO.c
	> Author: 
	> Mail: 
	> Created Time: Sat 08 Aug 2020 04:13:03 PM CST
 ************************************************************************/

#include"head.h"
#include"common.h"

int main() {
    char *tmp;
    if ((tmp = get_conf_2("./test.conf", "YPIR")) == NULL) {
        fprintf(stderr, "Error in conf\n");
        exit(1);
    }
    printf("%s\n", tmp);
    // printf("%s\n". conf_value);
    return 0;
}
