#!/bin/bash

if [ $# -ne 1 ]; then
    dialog --title "Ошибка" --msgbox "Неверное число параметров. Укажите имя файла для удаления" 0 0
    exit 1 
fi
 
if [[ ! -f "$1" ]]; then
    dialog --title "Ошибка" --msgbox "Указанный файл $1 не найден" 0 0
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
