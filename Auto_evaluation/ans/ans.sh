#!/bin/bash

declare -a num

read n

for ((i=1; i<=$n; i++)) do
    read num[$i]
done

cnt=0

for ((i=1; i<=$n; i++)) do
    sum1=0
    sum2=0
    for ((j=1; j<$i; j++)) do
        if [[ ${num[$j]} -gt ${num[$i]} ]]; then
            sum1=$[${sum1}+1]
        fi
    done
    for ((j=$[$i+1]; j<=$n; j++)) do
        if [[ ${num[$j]} -gt ${num[$i]} ]]; then
            sum2=$[${sum2}+1]
        fi
    done
    if [[ ${sum1} -eq ${sum2} ]]; then
        cnt=$[$cnt+1]
    fi
done

echo $cnt
