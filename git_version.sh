#!/bin/bash
GIT_VER_FILE=./libjson_config_git_version
GIT_VERSION_COMMIT_VER=`git rev-list HEAD | wc -l | awk '{print $1}' `
echo "GIT_VERSION_COMMIT_VER:" ${GIT_VERSION_COMMIT_VER}
GIT_VERSION=`git rev-list HEAD -n 1 | cut -c 1-7 `
echo "GIT_VERSION:" ${GIT_VERSION}

echo "GIT_VERSION_COMMIT="${GIT_VERSION_COMMIT_VER} >${GIT_VER_FILE}  2>&1 
echo "GIT_VERSION="${GIT_VERSION} >>${GIT_VER_FILE}  2>&1 

echo "Generate git version done!"
