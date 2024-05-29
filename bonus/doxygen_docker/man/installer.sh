#!/bin/bash
##
## EPITECH PROJECT, 2024
## my_zappy
## File description:
## installer.sh
##

TRUE=1
FALSE=0
DEBUG=$FALSE

function decho {
    if [ $DEBUG -eq $TRUE ]; then
        echo "$1"
    fi
}

function count_files_in_man_folder {
    decho "Counting files in man folder" >&2
    DIRECTORY="$1"/*.3
    FILE_COUNT=$(ls -1 $DIRECTORY 2>/dev/null | wc -l)
    decho "File count: $FILE_COUNT" >&2
    echo "$FILE_COUNT"
}

function get_files_in_man_folder {
    decho "In get file in man folder" >&2
    decho "PWD = $(pwd)" >&2
    DIRECTORY="$1"/*.3
    decho "Directory = $DIRECTORY, \$1 = $1" >&2
    if [ -z "$DIRECTORY" ]; then
        echo "No .3 files found in $1"
        return
    fi
    MAN_CONTENT=""
    decho "Files found:" >&2
    # Iterate over the files in the directory and append their names to the man page
    for file in $DIRECTORY; do
        # Extract the file name and remove the ".3" extension
        filename=$(basename "$file")
        filename_without_extension="${filename%.3}"
        decho "file: '$filename_without_extension'" >&2
        # Append the file name to the man page content
        MAN_CONTENT+="\n.B ${MAN_PROG_DIR}/${filename_without_extension}\n"
    done
    decho "Out of get file in man folder" >&2
    echo "$MAN_CONTENT"
}

function create_homepage_man {
    decho "In create homepage man" >&2
    decho "MAN_FOLDER='$4'" >&2
    FILE_COUNT=$(count_files_in_man_folder "$4")
    MAN_FILES=$(get_files_in_man_folder "$4")
    HOMEPAGE="
.\\\" Manpage for zappy project\n
.\\\" Contact: Your Name <your.email@example.com>\n
.TH ZAPPY 1 \"May 2024\" \"Version 1.0\" \"Zappy Manual\"\n
\n
.SH NAME\n
zappy \\- Welcome to Zappy!\n
\n
.SH SYNOPSIS\n
.B zappy\n
\n
.SH DESCRIPTION\n
The Zappy project is a game involving 3 binaries:\n
\n
\n
.SH OPTIONS\n
None.\n
\n
.SH SEE ALSO\n
.BR zappy-command (1),\n
.BR zappy-config (5),\n
.BR zappy-utility (7)\n
\n
.SH AUTHOR\n
Written by Your Name.\n
\n
.SH COPYRIGHT\n
This is free and unencumbered software released into the public domain.\n
\n
.SH BUGS\n
Please report any bugs to <your.email@example.com>.\n
\n
.SH NOTES\n
This man page is for informational purposes only. For detailed usage instructions, please refer to the specific manual pages listed under \"SEE ALSO\".\n
\n
.SH DISCLAIMER\n
This software is provided \"as is\" without warranty of any kind. Use at your own risk.\n
\n
.SH VERSION\n
1.0\n
\n
.SH DATE\n
May 2024
\n
.SH SUB-PAGE DUMP [${FILE_COUNT} file(s)] (very crude for now)\n
$MAN_FILES
"
    decho "Homepage generated" >&2
    mkdir -p "$1"
    if [ $DEBUG -eq $TRUE ]; then
        echo -e "$HOMEPAGE"
    fi
    echo -e "$HOMEPAGE" >"$1"/"$2"."$3"

}

function display_help() {
    echo "USAGE:"
    echo "       $0   [-h|--help|-d]"
    echo "PARAMETERS:"
    echo "       -h or --help is to display this help section"
    echo "       -d or --debug is to enable a debug display of the program"
}

# Check if administrator
if [ $# -ge 2 ]; then
    display_help
    exit 1
fi

if [ "$1" == "-h" ] || [ "$1" == "--help" ]; then
    display_help
    exit 0
fi

if [ "$(id -u)" -ne 0 ]; then
    echo "This script must be run as root."
    sudo $0 $@
    exit $?
fi

if [ "$1" == "-d" ] || [ "$1" == "--debug" ]; then
    DEBUG=$TRUE
else
    DEBUG=$FALSE
fi

# Define the installation directory for man pages
MAN_DIR="/usr/share/man/"
MAN_PROG_DIR="zappy"
MAN_DEST="${MAN_DIR}${MAN_PROG_DIR}"
MAN_SOURCE="./man3"

# Removing existing man pages if they exist
echo "Removing previous manual entries of this program if they existed"
decho "Removing '$MAN_DEST' entry if it exists"
if [ $DEBUG -eq $TRUE ]; then
    rm -rvf "$MAN_DEST"
else
    rm -rf "$MAN_DEST"
fi
STATUS=$?
if [ $STATUS -ne 0 ]; then
    echo "This operation failed, please re-run this program with -d or do the operation manually"
    exit $STATUS
fi
decho "Removing '$MAN_DIR/zappy.3' if it exists"
if [ $DEBUG -eq $TRUE ]; then
    rm -vf "$MAN_DIR/man3/zappy.3"
else
    rm -f "$MAN_DIR/man3/zappy.3"
fi
STATUS=$?
if [ $STATUS -ne 0 ]; then
    echo "This operation failed, please re-run this program with -d or do the operation manually"
    exit $STATUS
fi
decho "Removed '$MAN_DEST' and '$MAN_DIR/zappy.3' is they existed"
echo "Previous entries, if present, have been removed"

# Create the directory structure for your project's man pages
decho "Creating folder '$MAN_DEST'"
mkdir -p "$MAN_DEST"
STATUS=$?
if [ $STATUS -ne 0 ]; then
    echo "This operation failed, please re-run this program with -d or do the operation manually"
    exit $STATUS
fi
decho "Created folder '$MAN_DEST'"

# Copy or move your man pages into the appropriate directory
echo "Copying contents from the data folder to the man folder"
cd $MAN_SOURCE
STATUS=$?
if [ $STATUS -ne 0 ]; then
    echo "This operation failed, please re-run this program with -d or do the operation manually"
    exit $STATUS
fi
if [ $DEBUG -eq $TRUE ]; then
    cp -rvf * "$MAN_DEST"
else
    cp -rf * "$MAN_DEST"
fi
STATUS=$?
if [ $STATUS -ne 0 ]; then
    echo "This operation failed, please re-run this program with -d or do the operation manually"
    exit $STATUS
fi
cd ..
echo "Content of '$MAN_SOURCE' has been copied to '$MAN_DEST'"

# Creating the homepage
echo "Generating homepage"
create_homepage_man "$MAN_DEST" "zappy" "3" "$MAN_SOURCE"
STATUS=$?
if [ $STATUS -ne 0 ]; then
    echo "This operation failed, please re-run this program with -d or do the operation manually"
    exit $STATUS
fi
echo "Homepage has been generated"

# Create a symbolic link for the main man page
echo "Creating symbolic link of '$MAN_DEST/zappy.3' to '$MAN_DIR/zappy.3'"
ln -s "$MAN_DEST/zappy.3" "$MAN_DIR/man3/zappy.3"
STATUS=$?
if [ $STATUS -ne 0 ]; then
    echo "This operation failed, please re-run this program with -d or do the operation manually"
    exit $STATUS
fi
echo "Symbolic link created of '$MAN_DEST/zappy.3' to '$MAN_DIR/zappy.3'"

# Update the shell man paths to include the zappy folder
echo "Updating the shell man paths to include the zappy folder"
export MANPATH="/usr/local/man:/usr/local/share/man:/usr/share/man:$MAN_DEST:$MANPATH"
SHELL_PATHS=("/etc/bash.bashrc" "/etc/bashrc" "/etc/profile" "/etc/zsh/zshenv" "/etc/zshrc" "/etc/fish/config.fish")

SHELL_LINE="export MANPATH=\"/usr/local/man:/usr/local/share/man:/usr/share/man:$MAN_DEST:\$MANPATH\""
for i in "${SHELL_PATHS[@]}"; do
    # Check if the line is already present in the file
    if ! grep -qF "$SHELL_LINE" "$i"; then
        echo "$SHELL_LINE" >>"$i"
        decho "Added MANPATH to '$i'"
    else
        decho "MANPATH is already present in '$i' not adding"
    fi
done
echo "Updated the shell man paths to include the zappy folder"

echo "Installation complete. You can now use 'man zappy' to access the manual page."
echo "Please relaunch any terminal instances you have for the full effect of the new man pages to be applied"

# Update the man database
echo "Updating database"
mandb
STATUS=$?
if [ $STATUS -ne 0 ]; then
    echo "This operation failed, please re-run this program with -d or do the operation manually"
    exit $STATUS
fi
echo "Database updated"
echo "(C) Created by Henry Letellier"
echo "This program is provided as if and without any warranty"
