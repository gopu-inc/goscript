#!/bin/bash
# On compile vers le binaire 'gd'
mv src/fe.c src/gsc.c
mv src/fe.h src/gsc.c
gcc src/module.c src/gsc.c -DFE_STANDALONE -O3 -o gd -Wall -Wextra -std=c99 -pedantic
