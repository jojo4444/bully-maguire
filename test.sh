#!/bin/bash

goex() {
	exit 126
}

mkdir -p release || goex
cd release || goex
cmake .. -DCMAKE_BUILD_TYPE=Release || goex

rm -f test ans || goex

for i in $(seq 1 1)
do
	echo "10 random" | ./generator/generator > test || goex
	res=$(tail test -n 1)
	cat test | ./solution/solution > ans
	res2=$(tail ans -n 1)

	echo $res
	echo $res2
done