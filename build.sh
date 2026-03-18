#!/bin/bash
gcc src/module.c src/gsc.c -DFE_STANDALONE -O3 -o gd -Wall -Wextra -std=c99 -pedantic
