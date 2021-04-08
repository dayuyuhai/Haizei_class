#!/bin/bash

declare -a num

read n

read -a num

read x

t=${num[$n-1]}

for ((i=$n-1; i>=$x; i--)); do
    num[$i]=${num[$i-1]}
done

num[$x-1]=$t

for ((i=0; i<$n; i++)); do
    if [[ $i -ne 0 ]];then 
        echo -n " "
    fi
    echo -n ${num[$i]}
done
