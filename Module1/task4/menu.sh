#!/bin/sh
while true; do
  a=`dialog --title "MENU" \
    --stdout --menu "MENU HEADING" 0 0 0 1 "FIRST" 2 "SECOND" 3 "THIRD" 4 "FOURTH" 5 "FIFTH" 0 "END"`


    case $a in
            "1")
                dialog --title "Title" --backtitle "Background Title" \
                --msgbox "First entry selected" 0 0
                ;;
            "2")
                dialog --title "Title" --backtitle "Background Title" \
                --msgbox "Second entry selected" 0 0
                ;;
            "3")
                dialog --title "Title" --backtitle "Background Title" \
                --msgbox "Third entry selected" 0 0
                ;;
            "4")
                dialog --title "Title" --backtitle "Background Title" \
                --msgbox "Fourth entry selected" 0 0
                ;;
            "5")
                dialog --title "Title" --backtitle "Background Title" \
                --msgbox "Fifth entry selected" 0 0
                ;;
            "0")
                dialog --title "Title" --backtitle "Background Title" \
                --no-label "End of program" --yes-label "Continue" \
                --yesno "End of program?" 0 0
                if [ $? -eq 1 ]; then
                    exit
                fi
                ;;
        
    esac
done

