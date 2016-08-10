


"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv.com" projects\json_config_vs14.sln /rebuild "Debug|x64" 
echo %ERRORLEVEL%
IF NOT %ERRORLEVEL% EQU 0 (
echo "ERROR!!! Build failed here!" 
goto end)

"C:\Program Files (x86)\Microsoft Visual Studio 14.0\Common7\IDE\devenv.com" projects\json_config_vs14.sln /rebuild "Release|x64" 
echo %ERRORLEVEL%
IF NOT %ERRORLEVEL% EQU 0 (
echo "ERROR!!! Build failed here!" 
goto end)

echo "Build all succeed!"

:end
timeout 30
