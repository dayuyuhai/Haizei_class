#########################################################################
# File Name: 2-1.mems.sh
# Author: 北海望谷堆
# mail: dayuyuhai@outlook.com
# Created Time: Thu 08 Oct 2020 07:07:32 PM CST
#########################################################################
#!/bin/bash

free -m | grep "^Mem" | awk -v last_per=$1 -v nowdate=$(date +"%Y-%m-%d__%H:%M:%S") '
{
    printf("%s %sM %sM %.1f%% %.1f%%\n", nowdate, $2, $7, $3 / $2 * 100, 0.3 * last_per + 0.7 * ($3 / $2 * 100));
}'

