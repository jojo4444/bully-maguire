#!/bin/bash

goex() {
	echo "panica!"
	exit 126
}

mkdir -p release || goex
cd release || goex
cmake .. -DCMAKE_BUILD_TYPE=Release || goex

rm -f test ans || goex

for i in $(seq 1 1000)
do
	echo "10 random" | ./generator/generator > test || goex
	res=($(tail test -n 1))
	cat test | ./solution/solution > ans || goex
	res2=($(tail ans -n 1))

	for i in $(seq 0 2)
	do
		a=${res[i]}
		b=${res2[i]}

		bcres=$(echo "tmp=($a)-($b);tmp > -0.0001 && tmp < 0.0001" | bc -l)

		if [ "$bcres" != "1" ]
		then
			echo "Error!!!"
			echo "bcres: $bcres"
			echo "res: $res"
			echo "res2: $res2"
			goex
		fi
	done
done