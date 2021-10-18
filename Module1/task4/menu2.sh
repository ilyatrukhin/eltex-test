#!/bin/sh
options=""

a=`dialog --title "MENU" \
    --stdout --nocancel --menu "MENU HEADING" 0 0 0 /home/ilya/file1 "" /home/ilya/file2 "" /home/ilya/file3 ""`

if [ $? -eq 255 ]; then
    exit
else
  
dialog --title "Title" --backtitle "Background Title" \
--msgbox "$a" 0 0

fi
            

