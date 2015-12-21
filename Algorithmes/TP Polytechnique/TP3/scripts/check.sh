#!/bin/bash

for file in $1/*
do
	if [ $file != ${1}/expected.txt ]
	then
		arr=()
		echo $file
		for k in `head -n 1 $file`
		do
			arr+=($k)
		done
		tes=$((${arr[0]}+${arr[1]}))
		tess=`../TP3 -p -f $file -d $2 | tail -n $tes`
		a=`cat $file`
		b="${a}\n${tess}"
		echo -e "$b" | python3.4 check_solution.py | xargs echo $file, >> ../output/output_verif.csv
	fi
done