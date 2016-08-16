@echo off

for /f "tokens=1,2 delims==" %%i in (libjson_config_version) do set %%i=%%j

for /f "tokens=1,2 delims==" %%i in (libjson_config_git_version) do set %%i=%%j


set app_name_lowercase=libjson_config
set app_name=LIBJSON_CONFIG
set header_def=LIB_JSON_CONFIG_VERSION_H_
set header_file_location=.\src\libjson_config\libjson_config_version.h

echo %app_name_lowercase%_version %MAJOR_VERSION%.%MINOR_VERSION%.%REVISION_VERSION%.%git_ver%

echo /* DO NOT EDIT. This file (and "version") is generated by generate_version.bat. */ >%header_file_location% 2>&1
echo #ifndef %header_def% >>%header_file_location% 2>&1
echo #define %header_def% >>%header_file_location% 2>&1
echo #define %app_name%_VERSION_MAJOR           %MAJOR_VERSION% >>%header_file_location%  2>&1 
echo #define %app_name%_VERSION_MINOR           %MINOR_VERSION% >>%header_file_location%  2>&1 
echo #define %app_name%_VERSION_REVISION        %REVISION_VERSION% >>%header_file_location%  2>&1 
echo #define %app_name%_VERSION_STRING          "%MAJOR_VERSION%.%MINOR_VERSION%.%REVISION_VERSION%.r%GIT_VERSION_COMMIT%(%GIT_VERSION%)" >>%header_file_location%  2>&1 
echo #define %app_name%_VERSION_STRING_EX       "%app_name_lowercase% version:%MAJOR_VERSION%.%MINOR_VERSION%.%REVISION_VERSION%.r%GIT_VERSION_COMMIT%(%GIT_VERSION%) build at %date:~0,4%-%date:~5,5% %time:~0,8%" >>%header_file_location%  2>&1 
echo #endif >>%header_file_location%  2>&1 