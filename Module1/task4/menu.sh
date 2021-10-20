#!/bin/sh
while true; do
  a=`dialog --title "MENU" \
    --stdout --nocancel --menu "Выберите действие" 0 0 0 \
    1 "Удалить файл с созданием жесткой ссылки" \
    2 "Восстановить файл" \
    3 "Сделать резервную копию для $HOME/listtask/" \
    4 "Восстановить последнюю резервную копию в $HOME/listtask" \
    5 "Восстановить резервную копию в $HOME/listtask за определенную дату" \
    0 "Выход"`


    case $a in
            "1")
                user_input=$(\
                dialog --title "Удаление файла" \
                        --inputbox "Укажите имя файла:" 8 40 \
                3>&1 1>&2 2>&3 3>&- \
                )
                if [ "$user_input" != "" ]; then
                    ./scripts/remftrash.sh "scripts/$user_input" 
                   
                fi
                ;;
            "2")
                user_input=$(\
                dialog --title "Восстановление файла" \
                        --inputbox "Укажите полное или неполное имя файла:" 8 40 \
                3>&1 1>&2 2>&3 3>&- \
                )
                if [ "$user_input" != "" ]; then
                    ./scripts/unftrash.sh "$user_input"           
                fi
                ;;
            "3")
                ./scripts/makebackup.sh &&
                dialog --title "Info" --backtitle "" \
                --msgbox "Резервная копия создана" 0 0
                ;;
            "4")
                ./scripts/restorebackup.sh &&
                dialog --title "Info" --backtitle "" \
                --msgbox "Резервная копия восстановлена" 0 0
                ;;
            "5")
                user_input=$(\
                dialog --title "Откат " \
                        --inputbox "Укажите дату в формате YYMMDD:" 8 40 \
                3>&1 1>&2 2>&3 3>&- \
                )
                if [ "$user_input" != "" ]; then
                    ./scripts/rollbackstate.sh "$user_input" 
                fi
                ;;
            "0")
                dialog --title "Подтверждение действия" --backtitle "Background Title" \
                --no-label "Выйти" --yes-label "Отмена" \
                --yesno "Выйти?" 0 0
                if [ $? -eq 1 ]; then
                    exit
                fi
                ;;
        
    esac
done

