@echo off

set GIT_COMMAND_PATH="C:\Program Files (x86)\Git\cmd\"
set PATH=%PATH%;%GIT_COMMAND_PATH%

set GIT_VER_FILE=./libjson_config_git_version


for /f "delims=" %%t in ('git.exe rev-list HEAD  ^| find /v /c ""') do set GIT_VERSION_COMMIT_VER=%%t
echo "GIT_VERSION_COMMIT_VER:" %GIT_VERSION_COMMIT_VER%

for /f "delims=" %%t in ('git.exe rev-list HEAD -n 1') do set GIT_VERSION=%%t
set GIT_VERSION=%GIT_VERSION:~0,7%
echo "GIT_VERSION:" %GIT_VERSION%

echo GIT_VERSION_COMMIT=%GIT_VERSION_COMMIT_VER%>%GIT_VER_FILE% 2>&1
echo GIT_VERSION=%GIT_VERSION%>>%GIT_VER_FILE%  2>&1 

echo "Generate git version done!"

