#!/bin/bash

read n
if [[ $n%7 -eq 0 && $n%2 -ne 0 ]]; then
    echo "YES"
else
    echo "NO"
fi
