#!/bin/bash

actualBackup="$HOME/$(ls -F $HOME | grep / | grep Backup | sort -r | head -n 1)"
actualBackupLen=${#actualBackup}

pathToListtask="$HOME/listtask"

if [ $actualBackup != "$HOME/" ]; then
    while read -r line ; do
        filename="${line:actualBackupLen}"
        if [ "${filename%/*}" != "${filename}" ]; then
            mkdir -p "$pathToListtask/${filename%/*}"
        fi
        cp "$line" "$pathToListtask/$filename"
    done < <(find $actualBackup -type f | grep -vP '(?<!\d)\d{6}(?!\d)'$)
else
    dialog --title "Ошибка" --backtitle "" \
        --msgbox "Резервных копий не обнаружено" 0 0
    exit 1
fi