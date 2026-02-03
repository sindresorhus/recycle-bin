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

<nul set /p="Test case #4: Subst virtual drive: "
call :test_subst

<nul set /p="Test case #5: Chained subst drives: "
call :test_chained_subst

exit /b

:: Test case for subst virtual drives
:test_subst
    set target=%dir%
    mkdir %target%
    echo test > %target%\subst_test_file.txt

    :: Use Z: as the virtual drive (unlikely to be in use)
    subst Z: %cd%\%target%
    "%program%".exe Z:\subst_test_file.txt
    set result=%errorlevel%
    subst Z: /d

    if %result% == 0 (
        if exist %target%\subst_test_file.txt (
            echo FAILED
        ) else (
            echo PASSED
        )
    ) else (
        echo FAILED
    )

    :: Clean up
    "%program%".exe %target%
goto :eof

:: Test case for chained subst drives (Y: -> Z: -> real path)
:test_chained_subst
    set target=%dir%
    mkdir %target%
    echo test > %target%\chained_test_file.txt

    :: Create chain: Y: -> Z: -> real path
    subst Z: %cd%\%target%
    subst Y: Z:\
    "%program%".exe Y:\chained_test_file.txt
    set result=%errorlevel%
    subst Y: /d
    subst Z: /d

    if %result% == 0 (
        if exist %target%\chained_test_file.txt (
            echo FAILED
        ) else (
            echo PASSED
        )
    ) else (
        echo FAILED
    )

    :: Clean up
    "%program%".exe %target%
goto :eof

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
