@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build\VCVARSALL.BAT" amd64  -vcvars_ver=14.16.27023 > NUL 
echo PATH=%PATH%,INCLUDE=%INCLUDE%,LIB=%LIB%,WINDOWSSDKDIR=%WINDOWSSDKDIR% 
