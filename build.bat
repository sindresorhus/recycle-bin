@echo off

set filename=recycle-bin

gcc "%filename%".c -municode -O2 -lole32 -s -o "%filename%".exe -std=c99
