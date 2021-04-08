#!/bin/bash

num=(0 0 0 0 0 0 0 0 0 0)

read n x

for ((i=1; i<=$n; i++))
do
    temp=$i
    while [ $temp -ne 0 ]
    do
        t=$[$temp%10]
        temp=$[$temp/10]
        let num[$t]+=1
    done
done

echo ${num[$x]}
