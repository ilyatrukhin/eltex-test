#!/bin/bash

if [ $# -ne 1 ]; then
    dialog --title "Ошибка" --msgbox "Неверное число параметров. Укажите дату в формате YYMMDD для выбора резервной копии" 0 0
    exit 1 
fi

backup="$HOME/$(ls -F $HOME | grep / | grep Backup | grep $1 | sort -r | head -n 1)"
backupLen=${#backup}

pathToListtask="$HOME/listtask"

if [ $backup != "$HOME/" ]; then
    rm -rf "$pathToListtask"/*
    while read -r line ; do
        filename="${line:backupLen}"
        if [ "${filename%/*}" != "${filename}" ]; then
            mkdir -p "$pathToListtask/${filename%/*}"
        fi
        cp "$line" "$pathToListtask/$filename"
    done < <(find $backup -type f | grep -vP '(?<!\d)\d{6}(?!\d)'$)
else
    dialog --title "Ошибка" --backtitle "" \
        --msgbox "Резервных копий за указанную дату не обнаружено" 0 0
    exit 1
fi