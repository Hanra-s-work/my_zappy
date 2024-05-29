#!/bin/bash

# Check we are root
if [ "$EUID" -ne 0 ]; then
    echo "Please run as root"
    sudo $0 $@
    exit $?
fi

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

# The steps to the documentation
docker pull $DOCKER_NAME

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
docker rm -f ${DOCKER_CONTAINER}
docker run -i -d -v "$(pwd)":"/app" -v "$(pwd)/${OUTPUT_GENERATION}":"/${OUTPUT_GENERATION}" --name ${DOCKER_CONTAINER} ${DOCKER_NAME}
docker exec -i ${DOCKER_CONTAINER} /bin/bash -c "$RUN_COMMAND"
if [ $? -ne 0 ]; then
    echo "The documentation generation failed for the container"
    exit 1
fi

# Display generated content
ls -a
echo "Displaying the content of: ${OUTPUT_GENERATION}"
ls -a "${OUTPUT_GENERATION}"
echo "Displaying the content of: ${OUTPUT_GENERATION}/${HTML_GENERATION}"
ls -a "${OUTPUT_GENERATION}/${HTML_GENERATION}"
echo "Freeing no longer needed cache from the ram"
sh -c 'echo 3 > /proc/sys/vm/drop_caches'
