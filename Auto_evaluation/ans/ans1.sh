#!/bin/bash

read a b
a=$[$a*10+$b]
ans=$[$a/26]
echo $ans
