#!/bin/bash

echo "--QUALITY--"
./quality.sh ../input/bench2 $1
./quality.sh ../input/bench3 $1
./quality.sh ../input/benchBig $1
echo "--STD--"
./std.sh ../input/bench2 $1
./std.sh ../input/bench3 $1
./std.sh ../input/benchBig $1
./std.sh ../input/Biodome $1
./std.sh ../input/other $1
echo "--CHECK--"
./check.sh ../input/bench2 $1
./check.sh ../input/bench3 $1
./check.sh ../input/benchBig $1
./check.sh ../input/Biodome $1
./check.sh ../input/other $1