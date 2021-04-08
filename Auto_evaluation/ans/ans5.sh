#!/bin/bash
declare -a tree
read L M

for (( i=0; i<${M}; i++ ));do
    read S E
    for (( j=${S}; j<=${E}; j++ ));do
        tree[${j}]=1
    done
done

for (( i=0; i<=${L}; i++ ));do
    if [[ ${tree[$i]}x == x ]];then
        let sum=sum+1
    fi
done

echo $sum

