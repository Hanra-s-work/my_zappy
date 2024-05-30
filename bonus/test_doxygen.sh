#!/bin/bash

MY_USER=$USER
BASH_CWD=$(pwd)

function pause {
    echo "Press enter to continue..."
    read
}

# Check we are root
if [ "$EUID" -ne 0 ]; then
    echo "Please run as root"
    sudo $0 $@
    STATUS=$?
    if [ $STATUS -ne 0 ]; then
        echo "The program is exiting with error code: $STATUS probably because you refused to accord it elevated privileges"
    fi
    exit $STATUS
fi

# Free cache that is no longer needed (this could of been the result of other systems)
echo "Freeing no longer needed cache from the ram"
sh -c 'echo 3 > /proc/sys/vm/drop_caches'

# Creating alias for ls rebind
alias ls="ls --color=auto"

# environement
SETUP_FILE="setup.py"
TAG_FILE="version.txt"
IS_RELEASE="is_release.txt"
HTML_GENERATION=html
DOXYGEN_VERSION="1.8.20"
NOTIFY_CHANNEL="ntfy.sh/is_up"
COMMIT_TITLE="There is no title"
COMMIT_MESSAGE="There is no message"
DOCKER_NAME="hanralatalliard/doxygen"
DOXYFILE="bonus/doxygen_docker/Doxyfile"
CODING_STYLE_CONTAINER="ghcr.io/epitech/coding-style-checker:latest"
OUTPUT_GENERATION=documentation
LINUX_BINARY_FOLDER="./linux_binaries"
MAC_MONE_BINARY_FOLDER="./mac_mone_binaries"
MAC_INTEL_BINARY_FOLDER="./mac_intel_binaries"
CACHE_KEY=doxygen-cache-key
LINUX_CACHE_KEY_BUILD=linux-cache-key
MAC_MONE_CACHE_KEY_BUILD=mac-mone-cache-key
MAC_INTEL_CACHE_KEY_BUILD=mac-intel-cache-key
EXECUTABLES="./zappy_ai ./zappy_gui ./zappy_server"
EXECUTABLES_LINUX="./zappy_linux_ai ./zappy_linux_gui ./zappy_linux_server"
EXECUTABLES_MAC_INTEL="./zappy_mac_intel_ai ./zappy_mac_intel_gui ./zappy_mac_intel_server"
EXECUTABLES_MAC_MONE="./zappy_mac_apple_chip_ai ./zappy_mac_apple_chip_gui ./zappy_mac_apple_chip_server"
ICON_PATH=bonus/doxygen_docker/favicon/
MAN_INSTALL_PATH=bonus/doxygen_docker/man/installer.sh
HTML_SERVER_SPAWNER_PATH=bonus/doxygen_docker/html/launch_server.sh*
LINUX_ZIP_NAME=linux.zip
MAC_MON_ZIP_NAME=mac_apple_chip.zip
MAC_INTEL_ZIP_NAME=mac_intel_chip.zip
DOCUMENTATION_ZIP_NAME=documentation.zip

# Removing previous generated documentation
echo "Cleaning previous generation ${OUTPUT_GENERATION}"
# pause
rm -rf ${OUTPUT_GENERATION}
echo "Removing generated zip folders if present (from a previous run)"
rm -vf ${DOCUMENTATION_ZIP_NAME}
echo "Removing child dockers (from the previous generation)"
docker container prune -f

# The steps to the documentation
docker pull $DOCKER_NAME

# Clean built binaries
echo "Cleaning previous program build (if present)"
make fclean
echo "Removing python environement"
cd ./src/ai
make fclean_env
cd ../..

# Creating required folders
mkdir -p "${OUTPUT_GENERATION}" "${OUTPUT_GENERATION}/${HTML_GENERATION}"

# Create dummy page for html renders
HTML_CONTENT='<!DOCTYPE html><html lang="en"><head>'
HTML_CONTENT+=" <meta charset='UTF-8'>"
HTML_CONTENT+=" <meta name='viewport' content='width=device-width, initial-scale=1.0'>"
HTML_CONTENT+=" <title>Dummy Page</title>"
HTML_CONTENT+=" <style>"
HTML_CONTENT+="   body {font-family: Arial, sans-serif;background-color: #f8f9fa;color: #333;margin: 0;padding: 0;display: flex;justify-content: center;align-items: center;height: 100vh;}"
HTML_CONTENT+="   .container {text-align: center;padding: 20px;background: #fff;border: 1px solid #ddd;border-radius: 8px;box-shadow: 0 4px 8px rgba(0, 0, 0, 0.1);}"
HTML_CONTENT+="   h1 {color: #007bff;}"
HTML_CONTENT+="   p {font-size: 1.1em;}"
HTML_CONTENT+="   a {color: #007bff;text-decoration: none;}"
HTML_CONTENT+="   a:hover {text-decoration: underline;}"
HTML_CONTENT+=" </style>"
HTML_CONTENT+="</head><body>"
HTML_CONTENT+="<body>"
HTML_CONTENT+=" <div class='container'>"
HTML_CONTENT+="   <h1>Welcome to the Dummy Documentation</h1>"
HTML_CONTENT+="   <p>This is a placeholder page for generated documentation.<br>If you see this is that the doxyfile in the action did not generate html content (or generated it in the wrong place)</p>"
HTML_CONTENT+="   <p>To learn more, visit <a href="https://www.doxygen.org/">Doxygen</a>.</p>"
HTML_CONTENT+=" </div>"
HTML_CONTENT+="</body></html>"
echo -e "$HTML_CONTENT" >${OUTPUT_GENERATION}/${HTML_GENERATION}/index.html

# Run doxygen docker
DOCKER_CONTAINER=doxy
RUN_COMMAND="cd /app && cp ${DOXYFILE} ./Doxyfile && doxygen ; exit $?" # ${OUTPUT_GENERATION}
docker stop ${DOCKER_CONTAINER}
docker rm -f "${DOCKER_CONTAINER}"
docker run -i -d -v "$(pwd)":"/app" -v "$(pwd)/${OUTPUT_GENERATION}":"/${OUTPUT_GENERATION}" --name ${DOCKER_CONTAINER} ${DOCKER_NAME}
docker exec -i ${DOCKER_CONTAINER} /bin/bash -c "$RUN_COMMAND"
if [ $? -ne 0 ]; then
    echo "The documentation generation failed for the container"
    exit 1
fi
cd ${BASH_CWD}

# Display generated content
ls -a
echo "Displaying the content of: ${OUTPUT_GENERATION}"
ls -a "${OUTPUT_GENERATION}"
echo "Displaying the content of: ${OUTPUT_GENERATION}/${HTML_GENERATION}"
ls -a "${OUTPUT_GENERATION}/${HTML_GENERATION}":

# Update the content of the required content
echo "Content of temporary folder: ${OUTPUT_GENERATION}"
DOCUMENTATION=$(find ${OUTPUT_GENERATION}/* -maxdepth 1 -type d)
for i in ${DOCUMENTATION[@]}; do
    echo "\$i = '$i'"
    FINAL_PATH="$i/files/icon"
    echo "Final path = $FINAL_PATH"
    mkdir -p "$FINAL_PATH"
    cp -rv ${ICON_PATH}/* "$FINAL_PATH"
    ls -a -ls --color=auto "$FINAL_PATH"
done
cd ${BASH_CWD}

# Generating latex if present
if [ -e "${OUTPUT_GENERATION}/latex" ]; then
    cd "${OUTPUT_GENERATION}/latex"
    if [ -e "Makefile" ]; then
        CONT_NAME=loxygen
        COMMAND="cd /app && make"
        docker stop "$CONT_NAME"
        docker rm "$CONT_NAME"
        docker run -i -v "$(pwd)":"/app" --name "$CONT_NAME" ${DOCKER_NAME} /bin/bash -c "$COMMAND"
        docker stop "$CONT_NAME"
        docker rm "$CONT_NAME"
    else
        echo "No Makefile found, not generating anything"
    fi
    cd ../..
else
    echo "No latex folder found, not generating anything"
fi
cd ${BASH_CWD}

# Inject install files in the man (if present)
if [ -e "$OUTPUT_GENERATION/man" ]; then
    CWD=$(pwd)
    FILE_NAME="install_man.sh"
    cd "$OUTPUT_GENERATION/man"
    cp -v $CWD/$MAN_INSTALL_PATH ./$FILE_NAME
    chmod a+x $FILE_NAME
    cd $CWD
else
    echo "There was no man generated"
fi
cd ${BASH_CWD}

# Inject server spawner if present
if [ -e "$OUTPUT_GENERATION/html" ]; then
    CWD=$(pwd)
    FILE_NAME="launch_server.sh"
    cd "$OUTPUT_GENERATION/html"
    cp -v $CWD/$HTML_SERVER_SPAWNER_PATH ./$FILE_NAME
    chmod a+x $FILE_NAME
    cd $CWD
else
    echo "There was no html generated"
fi
cd ${BASH_CWD}

# Displaying the working directory
echo "pwd: $(pwd)"

# Zip the content
COMMAND_OPTIONS="-0 -r"
echo "Finding folders in ${OUTPUT_GENERATION}"
FORMATS=$(find ${OUTPUT_GENERATION} -maxdepth 1 -type d)
echo "Found folders in the documentation: $FORMATS"
# pause
# echo "Generating archive of $(basename "${OUTPUT_GENERATION}")"
# zip $COMMAND_OPTIONS ${DOCUMENTATION_ZIP_NAME} $(basename "${OUTPUT_GENERATION}")
# pause
for item in ${FORMATS[@]}; do
    echo "Raw path: $item"
    COMPILED_PATH="$item"
    # COMPILED_PATH=$(basename "./$COMPILED_PATH")
    echo "Creating zip archive: '$COMPILED_PATH'"
    # pause
    zip $COMMAND_OPTIONS ${item}.zip $COMPILED_PATH
    # pause
done
cd ${BASH_CWD}

# Reclaim ownership
echo "Owning the generated content (replacing root by the current user account)"
chown $MY_USER:$MY_USER -Rv $OUTPUT_GENERATION
echo "Granting all users read-write rights on the files"
chmod a+rw -Rv $OUTPUT_GENERATION
cd ${BASH_CWD}

# Display the final result
echo "Displaying the latest version of the build process"
ls -a ${OUTPUT_GENERATION}
cd ${BASH_CWD}

# Free cache that could of been created during the build process that is no longer required
echo "Freeing no longer needed cache from the ram"
sh -c 'echo 3 > /proc/sys/vm/drop_caches'
