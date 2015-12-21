#!/bin/bash

echo "name_of_solver, file_name, n, m, c, solution, duration" > output/output.csv

for file in ./input/*
do
	./vorace -f $file | grep "," >> output/output.csv
done

for file in ./input/*
do
	./dynamique -f $file | grep "," >> output/output.csv
done

for file in ./input/*
do
	./recuitSimule -f $file | grep "," >> output/output.csv
done
