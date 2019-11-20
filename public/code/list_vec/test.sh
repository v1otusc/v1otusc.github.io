#!/bin/bash
echo "(1)Element Size (2)Vector Time (3)List Time (4)Vector Size (5)List Size "
for i in {1..25..1}
do
	g++ main.cpp -O3 -std=c++14 -D ANALYSIS -D M=$i
	./a.out
done
rm a.out