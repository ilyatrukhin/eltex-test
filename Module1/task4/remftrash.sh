#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage remftrash <fileaname>"
    exit 1 
fi
 
if [[ ! -f "$1" ]]; then
    echo "File doesn't exist"
    exit 1
fi

pathToSrcFile="$PWD/$1"
id=$(date +%s)
hardlink="$1$id"

mkdir -p ~/.trash && 
ln $1 $hardlink &&
echo "$pathToSrcFile" >> ~/.trash.log &&
mv $hardlink ~/.trash/ &&
rm -f $1 &&
dialog --title "Info" --msgbox "Hard link in $HOME/.trash/$hardlink" 0 0
