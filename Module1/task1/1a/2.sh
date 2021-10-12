#!/bin/bash
total=0

for((;;))
do
read -p "Enter the number: " number
if [[ $(($number % 2)) -eq 0 ]]
then
	break
else
	total=$(($total + 1))
fi
done
echo $total
