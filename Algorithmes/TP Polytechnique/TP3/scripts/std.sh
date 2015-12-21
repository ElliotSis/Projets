#!/bin/bash

for file in $1/*
do
	if [ $file != ${1}/expected.txt ]
	then
		echo $file
		../TP3 -f $file -d $2 | tail -1 | xargs echo ${file}, >> ../output/output_std.csv
	fi
done