#!/bin/bash
declare -a w
read n
w[1]=1
w[2]=2
for ((i=3;i<=${n};i++));do
    w[$i]=$[${w[$[$i-1]]}+${w[$[$i-2]]}]
done

for ((i=1;i<=${n};i++));do
    echo -n "${w[$i]}"
    if [[ $i -ne ${n} ]];then
        echo -n " "
    fi
done
