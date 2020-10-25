#########################################################################
# File Name: 3-2.CPU.sh
# Author: 北海望谷堆
# mail: dayuyuhai@outlook.com
# Created Time: Sat 10 Oct 2020 09:13:19 PM CST
#########################################################################
#!/bin/bash
DATE=(`date +%F__%T`)
cpuload=(`cat /proc/loadavg | awk '{print $1,$2,$3}'`)
load1=${cpuload[0]}
load5=${cpuload[1]}
load15=${cpuload[2]}
tmp=(`cat /sys/class/hwmon/hwmon2/temp1_input`)
tmp=(`echo "scale=2;$tmp/1000" | bc`)

TIME_INTERVAL=0.5

LAST_CPU_INFO=$(cat /proc/stat | grep -w cpu | awk '{print $2,$3,$4,$5,$6,$7,$8}')
LAST_SYS_IDLE=$(echo $LAST_CPU_INFO | awk '{print $4}')
LAST_TOTAL_CPU_T=$(echo $LAST_CPU_INFO | awk '{print $1+$2+$3+$4+$5+$6+$7}')
sleep ${TIME_INTERVAL}
NEXT_CPU_INFO=$(cat /proc/stat | grep -w cpu | awk '{print $2,$3,$4,$5,$6,$7,$8}')
NEXT_SYS_IDLE=$(echo $NEXT_CPU_INFO | awk '{print $4}')
NEXT_TOTAL_CPU_T=$(echo $NEXT_CPU_INFO | awk '{print $1+$2+$3+$4+$5+$6+$7}')

#系统空闲时间
SYSTEM_IDLE=`echo ${NEXT_SYS_IDLE} ${LAST_SYS_IDLE} | awk '{print $1-$2}'`
#CPU总时间
TOTAL_TIME=`echo ${NEXT_TOTAL_CPU_T} ${LAST_TOTAL_CPU_T} | awk '{print $1-$2}'`
CPU_USAGE=`echo ${SYSTEM_IDLE} ${TOTAL_TIME} | awk '{printf "%.2f", 100-$1/$2*100}'`



echo -e "$DATE $load1 $load5 $load15 $CPU_USAGE $tmp℃  \c"
if [[ $tmp < 50 ]]; then
    Warning="normal"
elif [[ $tmp < 70 ]]; then
    Warning="note"
else 
    Warning="waring"
fi
echo $Warning
