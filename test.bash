#!/bin/bash

a=10
((a++))   # a = 11
echo $a
y=$((a+=10))   # y = 21
echo $a $y
((a -= 5))   # a = 16
echo $a