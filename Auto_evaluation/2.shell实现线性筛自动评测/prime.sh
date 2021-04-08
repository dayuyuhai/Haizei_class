#!/bin/bash
declare -a prime;
for (( i = 0; i < 10001; i++ ));do
    prime[$i]=0;
done
for (( i = 2; ${i}*${i} < 10001; i++ ));do
    if [[ prime[$i] -eq 0 ]];then
        for (( j = 2; $i*$j <  10001; j++));do
            prime[$[$i*$j]]=1;
        done
    fi
done
sum=0
for (( i = 2; i < 10001; i++ ));do
    if [[ prime[$i] -eq 0 ]];then
         sum=$[${sum}+${i}]
       # sum+=${i}
    fi
done
echo ${sum}
