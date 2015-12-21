#!/bin/bash

IFS=$'\r\n' GLOBIGNORE='*' :; e=($(cat ${1}/expected.txt))

let "i = 0"
for file in $1/*
do
	if [ $file != ${1}/expected.txt ]
	then
		echo $file
		../TP3 -f $file -d $2 -te ${e[i]} | grep -A1 "quality" | cut -c38- | xargs echo ${file}, >> ../output/output_quality.csv
		((i++))
	fi
done