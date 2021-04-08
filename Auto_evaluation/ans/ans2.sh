#!/bin/bash

read a b
ans=$[$a%$b]
if [[ $ans -eq 0 ]];then
    echo "YES"
else
    echo "NO"
fi
