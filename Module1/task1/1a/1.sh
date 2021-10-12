#!/bin/bash
totalstr=""
stopstr="q"
for ((;;))
do
read -p "Enter string: " str
if [[ "$str" != "$stopstr" ]]
then
	totalstr="$totalstr$str"	
else
	break
fi
done
echo $totalstr
