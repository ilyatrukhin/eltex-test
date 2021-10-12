#!/bin/bash

for((;;))
do
echo "1 - nano"
echo "2 - vi"
echo "3 - links"
echo "0 - exit"
read -p "Enter the option: " opt

case $opt in
        "1")
            nano
            ;;
        "2")
            vi
            ;;
        "3")
            links
            ;;
        "0")
            break
            ;;
        *) echo "invalid option";;
esac
done

