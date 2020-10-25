/*************************************************************************
	> File Name: test.c
	> Author: 
	> Mail: 
	> Created Time: Wed 21 Oct 2020 07:43:09 AM CST
 ************************************************************************/

#include "head.h"

int main() {
    cJSON *conf = get_cjson("time.json");
    cJSON *ob = get_json_valueobject(conf, "Slave");
    int ans = get_json_valueint(ob, "Timer", "Disk");
    printf("%d\n", ans);

    return 0;
}

