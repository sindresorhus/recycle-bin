@echo off

setlocal enabledelayedexpansion

:: Global settings
set program=recycle-bin
set dir=test
set name=a

:: Test cases
<nul set /p="Test case #1: Long directory names: "
call :test 100 5

<nul set /p="Test case #2: Deep folder hierarchy: "
call :test 20 20

<nul set /p="Test case #3: Deep hierarchy with long paths: "
call :test 200 20

exit /b

:: Test case procedure
:: Parameters: <filename-length> <hierarchy-depth>
:test
    :: Repeat filename
    set file=
    for /l %%i in (1, 1, %~1) do set file=!file!%name%

    :: Create initial directory
    set target=%dir%
    mkdir %target%

    :: Create folder hierarchy
    for /l %%i in (1, 1, %~2) do (
        set target=!target!\%file%
        mkdir %file%
        robocopy %file% !target! /MOVE >nul
    )

    :: Delete long path
    "%program%".exe !target!

    if %errorlevel% == 0 (
        if exist !target! (
            echo FAILED
        ) else (
            echo PASSED
        )
    ) else (
        echo FAILED
    )

    :: Clean up
    "%program%".exe %dir%
goto :eof
