#########################################################################
# File Name: 5.user.sh
# Author: 北海望谷堆
# mail: dayuyuhai@outlook.com
# Created Time: Sat 10 Oct 2020 07:52:56 PM CST
#########################################################################

#!/bin/bash
Time=(`date +%F__%T`)
#获取用户总数
eval $(awk -F: -v Sum=0 '{if ($3>=1000 && $3!=65534) {Sum+=1;printf("All["Sum"]=%s;",$1)}}\
    END {printf("UserSum=%d\n",Sum)}' /etc/passwd)
#3个最活跃用户
MostActiveUser=`last -w | cut -d " " -f 1 | grep -v wtmp | grep  -v reboot| grep "[a-zA-Z]" | sort | uniq -c | sort -k 1 -n -r | awk -v num=3 '{if(num>0){printf(" %s ",$2);num--}}' | cut -c 2-`
#获取管理员权限用户
eval $(awk -F: '{if ($3==1000) printf("User_1000=%s",$1)}' /etc/passwd)

Users=`cat /etc/group | grep sudo | cut -d : -f 4 | tr ',' ' '`

UserWithRoot=${User_1000}

for i in ${Users};do
    if [[ $i == ${User_1000} ]];then
        continue;
    fi
    UserWithRoot="${UserWithRoot},$i"
done

if [[ -r /etc/sudoers ]];then
    for i in ${All[*]};do
        grep -q -w "^${i}" /etc/sudoers #^行首开始 -q 静默模式 -w 限制符
        if [[ $? -eq 0 ]];then
            UserWithRoot="${UserWithRoot}, $i"
        fi
    done
fi

#当前在线人数

UserLogedIn=`w -h | awk '{printf(",%s_%s_%s",$1,$3,$2)}' | cut -c 2-`

echo "${Time} ${UserSum} [${MostActiveUser}] [${UserWithRoot}] [${UserLogedIn}] "
