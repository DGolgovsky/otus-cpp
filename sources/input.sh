#!/bin/bash

arr=("cmd33" "cmd2" "cmd3" "cmd4" "cmd5" "cmd6" "cmd7")
for (( i = 0; i < ${#arr[@]}; i++ )); do
	echo ${arr[$i]}
	sleep 1
done