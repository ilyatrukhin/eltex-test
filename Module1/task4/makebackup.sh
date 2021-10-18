#!/bin/bash

isBackupExist=false
backupName=
curDate="$(date +%y)$(date +%m)$(date +%d)"
backupReport="$HOME/backup-report"

while read -r line ; do
    if [ $(($curDate - ${line: -6})) -le 7 ]; then
        backupName="$line"
        isBackupExist=true
        break
    fi
done < <(find $HOME -maxdepth 1 -type d | grep "Backup-")

if [ "$isBackupExist" = false ]; then
    echo "New backup from $(date +%y) $(date +%m) $(date +%d)" >> $backupReport
    mkdir "$HOME/Backup-20$curDate"
    while read -r line ; do
        cp -R "$HOME/listtask/$line" "$HOME/Backup-20$curDate"
        echo $line >> $backupReport  
    done < <(ls $HOME/listtask)

else
    echo "Updated $backupName from $(date +%y) $(date +%m) $(date +%d)"
    #echo "Updated $backupName from $(date +%y) $(date +%m) $(date +%d)" >> $backupReport
    while read -r line ; do
        if [[ ! -f "$backupName/$line" && ! -d "$backupName/$line" ]]; then
            echo "File $backupName/$line doesn't exist. Copying ..."
            cp -R "$HOME/listtask/$line" "$backupName/$line"
        fi
        #echo $line >> $backupReport  

    done < <(ls $HOME/listtask)
fi
