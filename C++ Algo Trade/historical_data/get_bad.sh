#!/bin/sh

for file in *;do
	if [ $(cat "$file" | wc -l) == "46" ];then
		echo "$file" >> "remove.txt"
	fi
done
