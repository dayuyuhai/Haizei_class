#########################################################################
# File Name: 1-2.disk.sh
# Author: 北海望谷堆
# mail: dayuyuhai@outlook.com
# Created Time: Fri 09 Oct 2020 05:23:17 PM CST
#########################################################################
#!/bin/bash
Time=(`date +%F__%T`)
#获取数据
eval `df -T -m -x tmpfs -x devtmpfs | tail -n +2 | awk -v DiskSum=0 -v DiskLeft=0 '{printf("Pname["NR"]=%s;Psum["NR"]=%d;Pleft["NR"]=%d;Puseperc["NR"]=%s;",$7,$3,$4,$6);DiskSum+=$3;DiskLeft+=$5;} END {printf("Pnum=%d;DiskSum=%d;DiskLeft=%d;", NR, DiskSum, DiskLeft)}'`
for (( i = 1; i <= ${Pnum}; i++ ));do
    echo "$Time 1 ${Pname[$i]} ${Psum[$i]} ${Pleft[$i]} ${Puseperc[$i]}"
done

DiskPerc=$[ ( 100 - ${DiskLeft}*100/${DiskSum}) ]

echo "${Time} 0 disk ${DiskSum} ${DiskLeft} ${DiskPerc}%"
