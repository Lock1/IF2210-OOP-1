@echo off
REM  13519214 - Make script for Windows
g++ -Wall -Wextra -D_WINDOWS -o out/engimon.exe src/*.cpp 2> log/gpp-windows-log.txt
type log\gpp-windows-log.txt
