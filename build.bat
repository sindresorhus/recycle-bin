@echo off

set filename=recycle-bin

gcc "%filename%".c -municode -O2 -s -o "%filename%".exe -std=g99
