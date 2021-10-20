#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage unftrash <fileaname>"
    exit 1 
fi

MENU_OPTIONS1=
MENU_OPTIONS2=
count=0

while read -r line ; do
    count=$(($count + 1))
    MENU_OPTIONS1="$MENU_OPTIONS1$line $count " 
    # your code goes here
done < <(grep $1 $HOME/.trash.log)

#echo $MENU_OPTIONS1

pathToRestore=`dialog --title "Select file recovery path" \
    --stdout --nocancel --menu "" 0 0 0 ${MENU_OPTIONS1}`

if [ $? -eq 255 ]; then
    exit
else
    count=0
    while read -r line ; do
        count=$(($count + 1))
        MENU_OPTIONS2="$MENU_OPTIONS2$line $count " 
        # your code goes here
    done < <(ls -ap $HOME/.trash/ | grep -v / | grep $1)

    fileToRestore=`dialog --title "Select file to restore" \
        --stdout --nocancel --menu "" 0 0 0 ${MENU_OPTIONS2}`
    
    pathToRestore="${pathToRestore%/*}"

    if [[ ! -d "$pathToRestore" ]]; then
        pathToRestore="$HOME"
    fi

    if [ $fileToRestore != "" ]; then
        pathToRestore="$pathToRestore/$fileToRestore"
        pathHardLink="$HOME/.trash/$fileToRestore"

        ln $pathHardLink $pathToRestore &&
        rm -f $pathHardLink &&
        dialog --title "Info" --backtitle "" \
        --msgbox "File $pathHardLink has just restored in $pathToRestore" 0 0
    else
        dialog --title "Info" --backtitle "" \
        --msgbox "Nothing to restore" 0 0
    fi
fi