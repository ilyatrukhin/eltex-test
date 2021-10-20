#!/bin/bash

isBackupExist=false
backupName=
curDate="$(date +%y)$(date +%m)$(date +%d)"
backupReport="$HOME/backup-report"

pathToListtask="$HOME/listtask/"
pathToListtaskStrLen=${#pathToListtask}

while read -r line ; do
    if [ $(($curDate - ${line: -6})) -le 7 ]; then
        backupName="$line"
        isBackupExist=true
        break
    fi
done < <(find $HOME -maxdepth 1 -type d | grep "Backup-")

if [[ -f "$HOME/Backup-20$curDate" ]]; then
    dialog --title "Ошибка" --backtitle "" \
        --msgbox "Файл $HOME/Backup-20$curDate существует. Создание директории с таким именем невозможно!" 0 0
    exit 1
fi

if [ "$isBackupExist" = false ]; then
    # Create new backup
    echo "New backup from $(date +%y) $(date +%m) $(date +%d)" >> $backupReport
    mkdir "$HOME/Backup-20$curDate"
    while read -r line ; do
        cp -R "$pathToListtask$line" "$HOME/Backup-20$curDate"
        echo $line >> $backupReport  
    done < <(ls $pathToListtask)

else
    newFilesLog=""
    newExistFilesLog=""
    # Update backup"
    echo "Updated $backupName from $(date +%y) $(date +%m) $(date +%d)" >> $backupReport
    while read -r line ; do
        filename="${line:pathToListtaskStrLen}"
        if [[ ! -f "$backupName/$filename" ]]; then
            if [ "${filename%/*}" != "${filename}" ]; then
                mkdir -p "$backupName/${filename%/*}"
            fi
            cp "$line" "$backupName/$filename"
            newFilesLog="$newFilesLog$filename\n"
        else
            if [ $(stat -c%s "$backupName/$filename") -ne $(stat -c%s "$line") ]; then
                mv "$backupName/$filename" "$backupName/$filename-$(date +%y)$(date +%m)$(date +%d)"
                cp "$line" "$backupName/$filename"
                newExistFilesLog="$newExistFilesLog$filename $filename-$(date +%y)$(date +%m)$(date +%d)\n"
            fi
        fi

    done < <(find $pathToListtask -type f)
    if [ ${#newFilesLog} -ge 1 ]; then
        echo -ne $newFilesLog >> $backupReport
    fi
    if [ ${#newExistFilesLog} -ge 1 ]; then
        echo -ne $newExistFilesLog >> $backupReport
    fi
fi
