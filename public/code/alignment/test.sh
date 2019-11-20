#!/bin/bash

echo "2 4 8 16 32 64 128"

for i in {1..16..1}
do
	g++ main.cpp -O3 -std=c++11 -D M=$i
	for b in {1..120..1}
	do
		./a.out
	done
	echo " "
done
rm ./a.out