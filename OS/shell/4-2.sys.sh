#########################################################################
# File Name: 4-2.sys.sh
# Author: 北海望谷堆
# mail: dayuyuhai@outlook.com
# Created Time: Sat 10 Oct 2020 09:14:46 PM CST
#########################################################################
#!/bin/bash

#时间
time=`date +%Y-%m-%d__%H:%M:%S`

#主机名
hostname=`hostname`

#OS版本
OSv=`cat /etc/issue | cut -d ' ' -f 1-3 | tr ' ' '_'`

#内核版本
Uv=`cat /proc/version | cut -d ' ' -f 3`

#运行时间和负载
OStime=(`uptime | tr -s -c 'a-zA-Z0-9.:\n' ' ' | cut -d ' ' -f 3-4,6 | tr -s -c 'a-z0-9.\n' ' '`)

#平均负载
#fz=`uptime | tr -s -c 'a-zA-Z0-9.:\n' ' ' | cut -d ' ' -f 11-13 | tr -s -c 'a-z0-9.\n' ' '`
fz=`uptime | tr -s -c 'a-zA-Z0-9.:\n' ' ' | cut -d ' ' -f 9-11 | tr -s -c 'a-z0-9.\n' ' '`

#磁盘总量及占用比
cp=(`df | head -2 | tail -1 | tr -s -c '/a-z0-9\n' ' ' | cut -d ' ' -f 2,5`)
cp[0]=$[${cp[0]}/1000]

#内存总量及占用比
total=`free | head -2 | tail -1 | awk '{printf("%d", $2)}'`
total=$[${total}/1000]
free=`free | head -2 | tail -1 | awk '{printf("%d", $4)}'`
free=$[${free}/1000]
used=$[$total-$free]
bi=$[100*${used}/${total}]

#CPU温度
wd=`cat /sys/class/hwmon/hwmon2/temp1_input`
wd=`echo "scale=2;${wd}/1000" | bc`

#磁盘警报
if [[ ${cp[1]} -gt 90 ]];then
    note[0]="warning"
elif [[ ${cp[1]} -gt 80 ]];then
    note[0]="note"
else
    note[0]="normal"
fi

#内存警报
if [[ $bi -gt 90 ]];then
    note[1]="warning"
elif [[ $bi -gt 80 ]];then
    note[1]="note"
else
    note[1]="normal"
fi

#温度警报
if [[ $(echo "$wd>=90") = 1 ]];then
    note[2]="warning"
elif [[ $(echo "$wd>=80") = 1 ]];then
    note[2]="note"
else
    note[2]="normal"
fi

#输出
echo "$time $hostname $OSv $Uv ${OStime[0]}_${OStime[1]}_day,_${OStime[2]}_hours,_${OStime[3]}_minutes ${fz[0]} ${fz[1]} ${fz[2]} ${cp[0]} ${cp[1]}% $total ${bi}% $wd ${note[0]} ${note[1]} ${note[2]}"
