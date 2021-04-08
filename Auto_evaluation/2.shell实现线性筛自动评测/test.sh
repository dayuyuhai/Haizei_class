#!/bin/bash
sum=0

for (( i = 2; i <= 100; i++ ));do
    flag=0
    for (( j = 2; j < $i; j++ ));do
        if [[ $[$i%$j] -eq 0 ]];then
            flag=1
            break
        fi
    done
    if [[ ${flag} -eq 0 ]];then
        sum=$[$sum+$i]
    fi
done

echo 5736396






