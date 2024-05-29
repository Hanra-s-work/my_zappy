#!/bin/bash
##
## EPITECH PROJECT, 2024
## my_zappy
## File description:
## test_rename.sh
##

EXECUTABLES=("./zappy_ai" "./zappy_gui" "./zappy_server")
EXECUTABLES_LINUX=("./zappy_linux_ai" "./zappy_linux_gui" "./zappy_linux_server")
EXECUTABLES_MAC=("./zappy_mac_ai" "./zappy_mac_gui" "./zappy_mac_server")
EXECUTABLES="./zappy_ai ./zappy_gui ./zappy_server"
EXECUTABLES_LINUX="./zappy_linux_ai ./zappy_linux_gui ./zappy_linux_server"
EXECUTABLES_MAC="./zappy_mac_ai ./zappy_mac_gui ./zappy_mac_server"
IFS=' ' read -r -a EXE_ARRAY <<<"${EXECUTABLES}"
IFS=' ' read -r -a LINUX_EXE_ARRAY <<<"${EXECUTABLES_LINUX}"

if [ ${#EXE_ARRAY[@]} -ne ${#LINUX_EXE_ARRAY[@]} ]; then
    echo "::error ::Mismatch between the number of executables in EXECUTABLES and EXECUTABLES_LINUX"
    exit 1
fi

for i in "${!EXE_ARRAY[@]}"; do
    EXE="${EXE_ARRAY[$i]}"
    LEXE="${LINUX_EXE_ARRAY[$i]}"

    if [ ! -e "$EXE" ]; then
        echo "::error file=$EXE,line=1,endLine=0,title='NOT FOUND' ::The file '$EXE' does not exist"
        exit 1
    else
        mv $EXE $LEXE
    fi
done
