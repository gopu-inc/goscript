@echo off

rem download this:
rem https://nuwen.net/mingw.html

gcc src/gsc.c src/module.c -DFE_STANDALONE -O3 -o fe -Wall -Wextra -std=c99 -pedantic
strip gd.exe
