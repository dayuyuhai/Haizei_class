#########################################################################
# File Name: 6.bad_process.sh
# Author: 北海望谷堆
# mail: dayuyuhai@outlook.com
# Created Time: Fri 09 Oct 2020 05:44:51 PM CST
#########################################################################
#!/bin/bash
Time=`date +"%Y-%m-%d__%H:%M:%S"`

eval `ps -aux --sort=-%cpu | sed '1d' | awk -v Idx=0 '{if($3 < 1) {exit} else { Idx+=1; printf("Cpu_Pid["Idx"]=%s;",$2)}} END {printf("MaliceCpu=%s;", Idx)}'`
eval `ps -aux --sort=-%mem | sed '1d' | awk -v Idx=0 '{if($4 < 3) {exit} else { Idx+=1; printf("Mem_Pid["Idx"]=%s;",$2)}} END {printf("MaliceMem=%s;", Idx)}'`
if [[ (${MaliceCpu} -eq 0) && (${MaliceMem} -eq 0) ]]; then
    exit 0
else 
    sleep 1s
fi

Ind=0
if [[ ${MaliceCpu} -gt 0 ]]; then
    for i in ${Cpu_Pid[@]}; do
        eval `ps -aux -h -q $i | awk -v Idx=${Ind} '{if($3 < 1) {exit} else { Idx+=1; printf("Pname["Idx"]=%s; Pid["Idx"]=%s; User["Idx"]=%s; Cpu_Percent["Idx"]=%s; Mem_Percent["Idx"]=%s;", $11, $2, $1, $3, $4)}} END {printf("Ind=%s;", Idx)}'`
    done
fi

if [[ ${MaliceMem} -gt 0 ]]; then
    for i in ${Mem_Pid[@]}; do
        eval `ps -aux -h -q $i | awk -v Idx=${Ind} '{if($4 < 3) {exit} else { Idx+=1; printf("Pname["Idx"]=%s; Pid["Idx"]=%s; User["Idx"]=%s; Cpu_Percent["Idx"]=%s; Mem_Percent["Idx"]=%s;", $11, $2, $1, $3, $4)}} END {printf("Ind=%s;", Idx)}'`
    done
fi

for (( i = 1;  i <= Ind; ++i )); do
    echo "${Time} ${Pname[$i]} ${Pid[$i]} ${User[$i]} ${Cpu_Percent[$i]}% ${Mem_Percent[$i]}%"
done
