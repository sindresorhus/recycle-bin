@echo off

set filename=recycle-bin

gcc "%filename%".c -municode -O2 -lole32 -luuid -s -o "%filename%".exe -std=c17
